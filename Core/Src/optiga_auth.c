#include "authentication/optiga_auth.h"
#include "authentication/mbedtls/sha256.h"
#include "optiga/optiga_util.h"
#include "optiga/optiga_crypt.h"
#include "optiga/pal/pal.h"
#include "optiga/pal/pal_os_event.h"
#include "optiga/pal/pal_os_timer.h"
#include "optiga/pal/pal_gpio.h"
#include "optiga/pal/pal_i2c.h"
#include <string.h>

#define APPLICATION_ADDRESS 0x08020000
#define SHA_SIZE            32
#define SIGNATURE_SIZE      71
#define SIGNATURE_OID       0xE0E8

optiga_key_id_t public_key_oid = SIGNATURE_OID;

// Global OPTIGA util instance
optiga_util_t *me_util = NULL;
static volatile optiga_lib_status_t optiga_lib_status = OPTIGA_LIB_SUCCESS;

// External symbols from platform layer
extern pal_gpio_t optiga_vdd_0;
extern pal_gpio_t optiga_reset_0;
extern pal_i2c_t optiga_pal_i2c_context_0;
extern I2C_HandleTypeDef hi2c1;

// ---------- Internal Callbacks ----------
static void optiga_util_callback(void *context, optiga_lib_status_t return_status)
{
    optiga_lib_status = return_status;
}

static void optiga_crypt_callback(void *context, optiga_lib_status_t return_status)
{
    optiga_lib_status = return_status;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        pal_os_event_timer_tick();
    }
}

// ---------- I2C Scanner (for debugging) ----------
static void I2C_Scan(I2C_HandleTypeDef *hi2c)
{
    printf("Scanning I2C...\r\n");
    for (uint8_t addr = 0x01; addr < 0x33; addr++)
    {
        if (HAL_I2C_IsDeviceReady(hi2c, addr << 1, 1, 10) == HAL_OK)
        {
            printf("Device found at 0x%02X\r\n", addr);
        }
    }
}

// ---------- Global Function: optiga_init ----------
void optiga_init(void)
{
    pal_gpio_set_high(&optiga_vdd_0);
    HAL_Delay(10);

    optiga_lib_status_t return_status;
    me_util = optiga_util_create(0, optiga_util_callback, NULL);
    if (!me_util)
    {
        printf("❌ Failed to create OPTIGA util instance.\r\n");
        return;
    }

    I2C_Scan(&hi2c1);
    printf("Starting OPTIGA Trust M logic...\r\n");

    while (1)
    {
        optiga_lib_status = OPTIGA_LIB_BUSY;
        return_status = optiga_util_open_application(me_util, 0);
        if (return_status != OPTIGA_LIB_SUCCESS)
        {
            printf("optiga_util_open_application() failed immediately. Retrying...\r\n");
            continue;
        }

        HAL_Delay(100);
        while (optiga_lib_status == OPTIGA_LIB_BUSY)
        {
            pal_os_event_trigger_registered_callback();
        }

        if (optiga_lib_status == OPTIGA_LIB_SUCCESS)
        {
            printf("✅ OPTIGA Trust M initialized successfully.\r\n");
            break;
        }
        else
        {
            printf("❌ OPTIGA init async failed: 0x%04X. Retrying...\r\n", optiga_lib_status);
            HAL_Delay(2000);
        }
    }
}

// ---------- Internal Function ----------
static bool verify_firmware_signature(uint32_t size)
{
    uint32_t firmware_size = size - SIGNATURE_SIZE;
    const uint8_t *firmware_ptr = (const uint8_t *)APPLICATION_ADDRESS;

    uint8_t calc_hash[SHA_SIZE];
    uint8_t signature[SIGNATURE_SIZE];

    // 1. Calculate SHA-256 hash of firmware
    mbedtls_sha256_context ctx;
    mbedtls_sha256_init(&ctx);

    if (mbedtls_sha256_starts_ret(&ctx, 0) != 0 ||
        mbedtls_sha256_update_ret(&ctx, firmware_ptr, firmware_size) != 0 ||
        mbedtls_sha256_finish_ret(&ctx, calc_hash) != 0)
    {
        printf("❌ SHA-256 calculation failed.\r\n");
        mbedtls_sha256_free(&ctx);
        return false;
    }

    mbedtls_sha256_free(&ctx);
    printf("✅ SHA-256 hash calculated:\r\n");
    for (int i = 0; i < SHA_SIZE; i++)
        printf("%02X", calc_hash[i]);
    printf("\r\n");

    // 2. Copy signature from flash
    memcpy(signature, (uint8_t *)(APPLICATION_ADDRESS + firmware_size), SIGNATURE_SIZE);

    // 3. Read public key from OPTIGA
    uint8_t public_key[65];
    uint16_t public_key_len = sizeof(public_key);
    optiga_lib_status = optiga_util_read_data(me_util, SIGNATURE_OID, 0, public_key, &public_key_len);
    if (optiga_lib_status != OPTIGA_LIB_SUCCESS)
    {
        printf("❌ Failed to read public key from OID 0x%04X\r\n", SIGNATURE_OID);
        return false;
    }

    printf("✅ Public key (OID 0x%04X):\r\n", SIGNATURE_OID);
    for (int i = 0; i < public_key_len; i++)
        printf("%02X", public_key[i]);
    printf("\r\n");

    // 4. Verify signature using OPTIGA
    optiga_crypt_t *me_crypt = optiga_crypt_create(0, optiga_crypt_callback, NULL);
    if (!me_crypt)
    {
        printf("❌ Failed to create OPTIGA crypt instance!\r\n");
        return false;
    }

    optiga_lib_status = OPTIGA_LIB_BUSY;
    optiga_crypt_ecdsa_verify(me_crypt,
                               calc_hash, SHA_SIZE,
                               signature, SIGNATURE_SIZE,
                               OPTIGA_CRYPT_OID_DATA, &public_key_oid);

    while (optiga_lib_status == OPTIGA_LIB_BUSY)
        pal_os_event_trigger_registered_callback();

    optiga_crypt_destroy(me_crypt);

    if (optiga_lib_status != OPTIGA_LIB_SUCCESS)
    {
        printf("❌ Signature verification FAILED! Status: 0x%04X\r\n", optiga_lib_status);
        return false;
    }

    printf("✅ Firmware signature verified successfully.\r\n");
    return true;
}
void optiga_deinit(void)
{
    if (me_util != NULL)
    {
        optiga_util_destroy(me_util);
        me_util = NULL;
        printf("✅ OPTIGA util instance destroyed.\r\n");
    }

    // Optional: Power down or reset VDD if needed
    pal_gpio_set_low(&optiga_vdd_0);
    HAL_Delay(10);
    printf("🔌 OPTIGA VDD set low (powered down).\r\n");
}
// ---------- Global Function ----------
bool verify_firmware_integrity(uint32_t size)
{
    return verify_firmware_signature(size);
}
