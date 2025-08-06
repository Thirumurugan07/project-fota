#include "ymodem/common.h"
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Convert an Integer to a string
  * @param  p_str: The string output pointer
  * @param  intnum: The integer to be converted
  * @retval None
  */
void int_to_str(uint8_t* p_str, uint32_t intNum) {
	uint32_t i = 0, divider = 1000000000,pos = 0, status = 0;

	for (i = 0;i < 10;i++) {
		p_str[pos++] = (intNum/divider) + 48;
		intNum %= divider;
		divider /= 10;
		if ((p_str[pos-1] == '0') || (status == 0)) {
			pos = 0;
		}
		else {
			status++;
		}
	}
}

/**
  * @brief  Convert a string to an integer
  * @param  p_inputstr: The string to be converted
  * @param  p_intnum: The integer value
  * @retval 1: Correct
  *         0: Error
  */

uint32_t str_to_int(uint8_t *p_inputStr, uint32_t* p_intNum) {
	uint32_t i = 0, res = 0;
	  uint32_t val = 0;

	  if ((p_inputStr[0] == '0') && ((p_inputStr[1] == 'x') || (p_inputStr[1] == 'X')))
	  {
	    i = 2;
	    while ( ( i < 11 ) && ( p_inputStr[i] != '\0' ) )
	    {
	      if (IS_VALID_HEX(p_inputStr[i]))
	      {
	        val = (val << 4) + CONVERTHEX(p_inputStr[i]);
	      }
	      else
	      {
	        /* Return 0, Invalid input */
	        res = 0;
	        break;
	      }
	      i++;
	    }

	    /* valid result */
	    if (p_inputStr[i] == '\0')
	    {
	      *p_intNum= val;
	      res = 1;
	    }
	  }
	  else /* max 10-digit decimal input */
	  {
	    while ( ( i < 11 ) && ( res != 1 ) )
	    {
	      if (p_inputStr[i] == '\0')
	      {
	        *p_intNum = val;
	        /* return 1 */
	        res = 1;
	      }
	      else if (((p_inputStr[i] == 'k') || (p_inputStr[i] == 'K')) && (i > 0))
	      {
	        val = val << 10;
	        *p_intNum = val;
	        res = 1;
	      }
	      else if (((p_inputStr[i] == 'm') || (p_inputStr[i] == 'M')) && (i > 0))
	      {
	        val = val << 20;
	        *p_intNum = val;
	        res = 1;
	      }
	      else if (ISVALIDDEC(p_inputStr[i]))
	      {
	        val = val * 10 + CONVERTDEC(p_inputStr[i]);
	      }
	      else
	      {
	        /* return 0, Invalid input */
	        res = 0;
	        break;
	      }
	      i++;
	    }
	  }

	  return res;
}

/**
  * @brief  Print a string on the HyperTerminal
  * @param  p_string: The string to be printed
  * @retval None
  */

void serial_put_string(uint8_t* p_string) {
	 uint16_t length = 0;

	  while (p_string[length] != '\0')
	  {
	    length++;
	  }
	  HAL_UART_Transmit(&UartHandle, p_string, length, TX_TIMEOUT);
}

/**
  * @brief  Transmit a byte to the HyperTerminal
  * @param  param The byte to be sent
  * @retval HAL_StatusTypeDef HAL_OK if OK
  */

HAL_StatusTypeDef serial_put_byte(uint8_t param) {
	/* May be timeouted... */
	  if ( UartHandle.gState == HAL_UART_STATE_TIMEOUT )
	  {
	    UartHandle.gState = HAL_UART_STATE_READY;
	  }
	  return HAL_UART_Transmit(&UartHandle, &param, 1, TX_TIMEOUT);
}
