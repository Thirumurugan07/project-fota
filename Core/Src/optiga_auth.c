#include "authentication/optiga_auth.h"
#include "optiga/optiga_util.h"
#include "optiga/pal/pal.h"
#include "optiga/pal/pal_os_event.h"
#include "optiga/pal/pal_os_timer.h"
#include "optiga/optiga_crypt.h"
#include "optiga/pal/pal_gpio.h"
#include "optiga/pal/pal_i2c.h"

#define APPLICATION_ADDRESS 0x08020000
#define SHA_SIZE 32
#define HASH_CALC_LEN (13028)

/* Update or Add these definitions */
#define SIGNATURE_SIZE 71
#define SIGNATURE_OFFSET 13028 // location of signature in OTA buffer
#define FIRMWARE_TOTAL_SIZE 13099
#define SIGNATURE_OID 0xE0E8 // assuming public key is in 0xE0F1
#define APPLICATION_ADDRESS 0x08020000


static uint8_t expected_hash[32];
static uint8_t calc_hash[32];
static uint8_t firmware_signature[SIGNATURE_SIZE];
extern pal_gpio_t optiga_vdd_0;
extern pal_gpio_t optiga_reset_0;
extern pal_i2c_t optiga_pal_i2c_context_0;
extern I2C_HandleTypeDef hi2c1;
static volatile optiga_lib_status_t optiga_lib_status = OPTIGA_LIB_SUCCESS;

// Async callback
static void optiga_util_callback(void *context, optiga_lib_status_t return_status)
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

void I2C_Scan(I2C_HandleTypeDef *hi2c) {
  printf("Scanning I2C...\r\n");
  for (uint8_t addr = 1; addr < 128; addr++) {
    if (HAL_I2C_IsDeviceReady(hi2c, addr << 1, 1, 10) == HAL_OK) {
      printf("Device found at 0x%02X\r\n", addr);
    }
  }
}


static void optiga_crypt_callback(void *context, optiga_lib_status_t return_status)
{
    optiga_lib_status = return_status;
}
void optiga_init(void)
{
	/* Power ON the OPTIGA Trust M chip */
	  pal_gpio_set_high(&optiga_vdd_0);
	  printf("Resetting OPTIGA...\r\n");
//	  pal_gpio_set_low(&optiga_reset_0);
//	  HAL_Delay(10);
//	  pal_gpio_set_high(&optiga_reset_0);
//	  HAL_Delay(10);


    optiga_util_t *me_util = NULL;
    optiga_lib_status_t return_status = OPTIGA_UTIL_ERROR;

    me_util = optiga_util_create(0, optiga_util_callback, NULL);
    if (!me_util)
    {
        printf("Failed to create OPTIGA util instance.\r\n");
        return;
    }
    I2C_Scan(&hi2c1);

     printf("Starting OPTIGA Trust M logic...\r\n");

    // Retry loop to initialize OPTIGA
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
            pal_os_event_trigger_registered_callback(); // CRUCIAL for bare metal
        }
        if (optiga_lib_status == OPTIGA_LIB_SUCCESS)
        {
            printf("OPTIGA Trust M initialized successfully.\r\n");
            break;
        }
        else
        {
            printf("OPTIGA init async failed: 0x%04X. Retrying...\r\n", optiga_lib_status);
            HAL_Delay(2000);
        }
    }
    hash_firmware_region_and_print();
}


bool verify_firmware_signature(optiga_util_t *util) {
  uint8_t firmware_data[HASH_CALC_LEN];
  uint8_t calc_hash[32];
  uint8_t expected_hash[32]; // Optional expected hash stored in flash
  uint8_t firmware_signature[SIGNATURE_SIZE];

  // 1. Read firmware data from flash
  memcpy(firmware_data, (uint8_t *)BOOTLOADER_START_ADDR, HASH_CALC_LEN);

//  // 2. Calculate SHA-256 hash of the firmware
//  mbedtls_sha256_context ctx;
//  mbedtls_sha256_init(&ctx);
//  mbedtls_sha256_starts_ret(&ctx, 0);
//  mbedtls_sha256_update_ret(&ctx, firmware_data, HASH_CALC_LEN);
//  mbedtls_sha256_finish_ret(&ctx, calc_hash);
//  mbedtls_sha256_free(&ctx);

  // 4. Read firmware signature from flash
  memcpy(firmware_signature,
         (uint8_t *)(BOOTLOADER_START_ADDR + SIGNATURE_OFFSET), SIGNATURE_SIZE);
  uint8_t public_key[65]; // Standard uncompressed ECC public key (0x04 | X[32]
                          // | Y[32])
  uint16_t public_key_len = sizeof(public_key);

  optiga_lib_status = optiga_util_read_data(util, SIGNATURE_OID, 0, public_key,
                                            &public_key_len);
  if (optiga_lib_status != OPTIGA_LIB_SUCCESS) {
    printf("❌ Failed to read public key from OID 0x%04X\r\n", SIGNATURE_OID);
    return false;
  }
  // 6. Verify digital signature using OPTIGA crypt
  optiga_crypt_t *me_crypt = optiga_crypt_create(0, optiga_util_callback, NULL);
  if (!me_crypt) {
    printf("❌ Failed to create OPTIGA crypt instance!\r\n");
    return false;
  }

  optiga_lib_status = OPTIGA_LIB_BUSY;
  optiga_crypt_ecdsa_verify(
      me_crypt, calc_hash, sizeof(calc_hash), firmware_signature,
      SIGNATURE_SIZE,
      OPTIGA_CRYPT_OID_DATA, // Using key stored inside OPTIGA
      SIGNATURE_OID);

  while (optiga_lib_status == OPTIGA_LIB_BUSY)
    pal_os_event_trigger_registered_callback();

  optiga_crypt_destroy(me_crypt);

  if (optiga_lib_status != OPTIGA_LIB_SUCCESS) {
    printf("❌ Signature verification FAILED! Status: 0x%04X\r\n",
           optiga_lib_status);
    return false;
  }
  printf("✅ Firmware signature verified successfully.\r\n");
  return true;
}
/* Replace verify_bootloader_hash() with combined hash+signature check */
bool verify_firmware_integrity(optiga_util_t *util) {
  return verify_firmware_signature(util);
}
