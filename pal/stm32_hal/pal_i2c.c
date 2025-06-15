#include "optiga/pal/pal_i2c.h"
#include "stm32f4xx_hal.h"  // Adjust for your STM32 series

#define PAL_I2C_MASTER_MAX_BITRATE  (400U)

static volatile uint32_t g_entry_count = 0;
static pal_i2c_t * gp_pal_i2c_current_ctx;

static pal_status_t pal_i2c_acquire(const void * p_i2c_context)
{
    (void)p_i2c_context;
    if (0 == g_entry_count)
    {
        g_entry_count++;
        return PAL_STATUS_SUCCESS;
    }
    return PAL_STATUS_FAILURE;
}

static void pal_i2c_release(const void * p_i2c_context)
{
    (void)p_i2c_context;
    g_entry_count = 0;
}

static void invoke_upper_layer_callback(const pal_i2c_t * p_pal_i2c_ctx, optiga_lib_status_t event)
{
    if (p_pal_i2c_ctx->upper_layer_event_handler != NULL)
    {
        ((upper_layer_callback_t)(p_pal_i2c_ctx->upper_layer_event_handler))(
            p_pal_i2c_ctx->p_upper_layer_ctx, event);
    }
    pal_i2c_release(p_pal_i2c_ctx->p_upper_layer_ctx);
}

pal_status_t pal_i2c_init(const pal_i2c_t * p_i2c_context)
{
    // Typically handled by MX or HAL init elsewhere
    (void)p_i2c_context;
    return PAL_STATUS_SUCCESS;
}

pal_status_t pal_i2c_deinit(const pal_i2c_t * p_i2c_context)
{
    (void)p_i2c_context;
    return PAL_STATUS_SUCCESS;
}

pal_status_t pal_i2c_write(const pal_i2c_t * p_i2c_context, uint8_t * p_data, uint16_t length) {
    pal_status_t status = PAL_STATUS_FAILURE;

    if (PAL_STATUS_SUCCESS == pal_i2c_acquire(p_i2c_context))
    {
    	gp_pal_i2c_current_ctx = (pal_i2c_t *)p_i2c_context;
        HAL_StatusTypeDef hal_status = HAL_I2C_Master_Transmit(
            (I2C_HandleTypeDef *)(p_i2c_context->p_i2c_hw_config),
            (uint16_t)(p_i2c_context->slave_address << 1),
            p_data,
            length,
            HAL_MAX_DELAY);

        if (hal_status == HAL_OK)
        {
            invoke_upper_layer_callback(p_i2c_context, PAL_I2C_EVENT_SUCCESS);
            status = PAL_STATUS_SUCCESS;
        }
        else
        {
            invoke_upper_layer_callback(p_i2c_context, PAL_I2C_EVENT_ERROR);
        }
    }
    else
    {
        status = PAL_STATUS_I2C_BUSY;
        invoke_upper_layer_callback(p_i2c_context, PAL_I2C_EVENT_BUSY);
    }

    return status;
}

pal_status_t pal_i2c_read(const pal_i2c_t * p_i2c_context, uint8_t * p_data, uint16_t length)
{
    pal_status_t status = PAL_STATUS_FAILURE;

    if (PAL_STATUS_SUCCESS == pal_i2c_acquire(p_i2c_context))
    {
    	gp_pal_i2c_current_ctx = (pal_i2c_t *)p_i2c_context;
        HAL_StatusTypeDef hal_status = HAL_I2C_Master_Receive(
            (I2C_HandleTypeDef *)(p_i2c_context->p_i2c_hw_config),
            (uint16_t)(p_i2c_context->slave_address << 1),
            p_data,
            length,
            HAL_MAX_DELAY);

        if (hal_status == HAL_OK)
        {
            invoke_upper_layer_callback(p_i2c_context, PAL_I2C_EVENT_SUCCESS);
            status = PAL_STATUS_SUCCESS;
        }
        else
        {
            invoke_upper_layer_callback(p_i2c_context, PAL_I2C_EVENT_ERROR);
        }
    }
    else
    {
        status = PAL_STATUS_I2C_BUSY;
        invoke_upper_layer_callback(p_i2c_context, PAL_I2C_EVENT_BUSY);
    }

    return status;
}

pal_status_t pal_i2c_set_bitrate(const pal_i2c_t * p_i2c_context, uint16_t bitrate)
{
    // Not applicable for STM32 HAL — config is done via CubeMX
    (void)p_i2c_context;
    (void)bitrate;
    return PAL_STATUS_SUCCESS;
}
