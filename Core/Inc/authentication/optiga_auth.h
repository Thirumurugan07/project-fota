#ifndef OPTIGA_AUTH_H
#define OPTIGA_AUTH_H

#include "optiga/optiga_util.h"
#include "optiga/pal/pal.h"
#include "optiga/pal/pal_os_event.h"
#include "optiga/pal/pal_os_timer.h"
#include "optiga/pal/pal_gpio.h"
#include "optiga/pal/pal_i2c.h"
#include "stm32f4xx_hal.h"  // Or your MCU header
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void optiga_init(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
bool verify_firmware_integrity(uint32_t size);
void optiga_deinit(void);
#ifdef __cplusplus
}
#endif

#endif /* OPTIGA_APP_H */
