#ifndef __COMMON_H
#define __COMMON_H


#include "stm32f4xx.h"
#include "stm32f401xe.h"


/* Constants used by Serial terminal */
#define TX_TIMEOUT (uint32_t)100
#define RX_TIMEOUT HAL_MAX_DELAY


/* exported macros -------------------------------------------------------*/

#define IS_CAP_LETTER(c)  (((c) >= 'A') && ((c) <= 'F'))
#define IS_LC_LETTER(c)  (((c) >= 'a') && ((c) <= 'f'))
#define IS_09(c)  (((c) >= '0') && ((c) <= '9'))
#define IS_VALID_HEX(c) (IS_CAP_LETTER(c) || IS_LC_LETTER(c) || IS_09(c))
#define ISVALIDDEC(c)       IS_09(c)
#define CONVERTDEC(c)       (c - '0')

#define CONVERTHEX_ALPHA(c) (IS_CAP_LETTER(c) ? ((c) - 'A'+10) : ((c) - 'a'+10))
#define CONVERTHEX(c)       (IS_09(c) ? ((c) - '0') : CONVERTHEX_ALPHA(c))

/* exported functions --------------------------------------------------------------*/

void int_to_str(uint8_t* p_str,uint32_t intNum);
uint32_t str_to_int(uint8_t* p_str, uint32_t *intNum);
void serial_put_string(uint8_t* p_string);
HAL_StatusTypeDef serial_put_byte(uint8_t param);


#endif
