/*
 * menu.c
 *
 *  Created on: 25 July 2023
 *      Author: Akash Virendra
 */

/* Includes ------------------------------------------------------------------*/
#include "ymodem/ymodem.h"
#include "ymodem/menu.h"
#include "main.h"
#include "ymodem/flash_if.h"
#include "ymodem/common.h"
#include "authentication/optiga_auth.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

pFunction jumpToApplication;
uint32_t jumpAddress, flashProtection;
uint8_t aFileName[FILE_NAME_LENGTH];

/* Private function prototypes -----------------------------------------------*/
void serial_download(void);
void serial_upload(void);

/**
  * @brief  Download a file via serial port
  * @param  None
  * @retval None
  */
void serial_download(void) {
	uint8_t number[11] = {0};
	uint32_t size = 0;
	COM_StatusTypeDef result = COM_OK;
	serial_put_string((uint8_t *)"Waiting for the file to be sent ... (press 'a' to abort)\n\r");

	if (FLASH_IF_erase(APPLICATION_ADDRESS) != FLASHIF_OK) {
		serial_put_string((uint8_t*)"Error occured while erasing the flash");
	}

	result = ymodem_receive(&size);

	if (result == COM_OK) {
			serial_put_string((uint8_t *)"\n\n\r Programming Completed Successfully!\n\r--------------------------------\r\n Name: ");
			serial_put_string((uint8_t *)aFileName);
		    int_to_str(number, size);
		    serial_put_string((uint8_t *)"\n\r Size: ");
		    serial_put_string((uint8_t *)number);
		    serial_put_string((uint8_t *)" Bytes\r\n");
		    serial_put_string((uint8_t *)"-------------------\r\n");
	}
	else if (result == COM_ABORT) {
		serial_put_string((uint8_t*)"\r\n\nAborted by User.\n\r");
	}
	else if (result == COM_LIMIT) {
		serial_put_string((uint8_t*)"\n\n\rThe image size is higher than the allowed space memory!\n\r");
	}
	else if (result == COM_DATA) {
		serial_put_string((uint8_t *)"\n\n\rVerification failed!\n\r");
	}
	else
	  {
		serial_put_string((uint8_t *)"\n\rFailed to receive the file!\n\r");
	  }
	  optiga_init();

	if ( verify_firmware_integrity(size) != 0) {
		optiga_deinit();
		serial_put_string("Firmware Authenticated!\r\n");
		serial_put_string((uint8_t *)"Start program execution......\r\n\n");
		      /* execute the new program */
		      jumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
		      /* Jump to user application */
		      jumpToApplication = (pFunction)jumpAddress;
		      /* Initialize user application's Stack Pointer */
		      __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
		      jumpToApplication();

	}
	else {
		optiga_deinit();
		serial_put_string("Firmware Not Authenticated!\r\nHALT!!!\r\n");
		while (1);
	}
}

/**
  * @brief  Upload a file via serial port.
  * @param  None
  * @retval None
  */

void serial_upload(void) {
	 uint8_t status = 0;
	 serial_put_string((uint8_t *)"\n\n\rSelect Receive File\n\r");
	 HAL_UART_Receive(&UartHandle, &status, 1, RX_TIMEOUT);
	 if ( status == CRC16)
	   {
	     /* Transmit the flash image through ymodem protocol */
	     status = ymodem_transmit((uint8_t*)APPLICATION_ADDRESS, (const uint8_t*)"UploadedFlashImage.bin", USER_FLASH_SIZE);

	     if (status != 0)
	     {
	       serial_put_string((uint8_t *)"\n\rError Occurred while Transmitting File\n\r");
	     }
	     else
	     {
	    	 serial_put_string((uint8_t *)"\n\rFile uploaded successfully \n\r");
	     }
	   }
}

/**
  * @brief  Display the Main Menu on HyperTerminal
  * @param  None
  * @retval None
  */

void main_menu(void) {
	 uint8_t key = 0;

	 serial_put_string((uint8_t *)"\r\n======================================================================");
	 serial_put_string((uint8_t *)"\r\n=                                                                    =");
	 serial_put_string((uint8_t *)"\r\n= Secure Booting and Firmware Update with hardware root of trust(1.1)=");
	 serial_put_string((uint8_t *)"\r\n=                                                                    =");
	 serial_put_string((uint8_t *)"\r\n=                                   By STM Application Team          =");
	 serial_put_string((uint8_t *)"\r\n======================================================================");
	 serial_put_string((uint8_t *)"\r\n\r\n");
	  FLASH_IF_disable_all_protection();

	  while (1)
	  {

		  serial_put_string((uint8_t *)"\r\n=================== Main Menu ============================\r\n\n");
		  serial_put_string((uint8_t *)"  Download image to the internal Flash ----------------- 1\r\n\n");
		  serial_put_string((uint8_t *)"  Upload image from the internal Flash ----------------- 2\r\n\n");
		  serial_put_string((uint8_t *)"  Execute the loaded application ----------------------- 3\r\n\n");

		  flashProtection = FLASH_IF_get_write_protection_status();

	    if(flashProtection == FLASHIF_PROTECTION_WRPENABLED)
	    {
	    	serial_put_string((uint8_t *)"  Disable the write protection ------------------------- 4\r\n\n");
	    }
	    else
	    {
	    	serial_put_string((uint8_t *)"  Enable the write protection -------------------------- 4\r\n\n");
	    }
	    serial_put_string((uint8_t *)"==========================================================\r\n\n");

	    /* Clean the input path */
	    __HAL_UART_FLUSH_DRREGISTER(&UartHandle);
	//    __HAL_UART_CLEAR_OREFLAG(&UartHandle);

	    /* Receive key */
	    HAL_UART_Receive(&UartHandle, &key, 1, RX_TIMEOUT);



	    switch (key)
	    {
	    case '1' :
	      /* Download user application in the Flash */
	      serial_download();
	      break;
	    case '2' :
	      /* Upload user application from the Flash */
	      serial_upload();
	      break;
	    case '3' :
	    	serial_put_string((uint8_t *)"Start program execution......\r\n\n");
	      /* execute the new program */
	      jumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
	      /* Jump to user application */
	      jumpToApplication = (pFunction)jumpAddress;
	      /* Initialize user application's Stack Pointer */
	      __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
	      jumpToApplication();
	      break;
	    case '4' :

	      if (flashProtection != FLASHIF_PROTECTION_NONE)
	      {
	        /* Disable the write protection */
	        if (FLASH_IF_write_protection_config(FLASHIF_WRP_DISABLE) == FLASHIF_OK)
	        {
	        	serial_put_string((uint8_t *)"Write Protection disabled...\r\n");
	        	serial_put_string((uint8_t *)"System will now restart...\r\n");
	        }
	        else
	        {
	        	serial_put_string((uint8_t *)"Error: Flash write un-protection failed...\r\n");
	        }
	      }
	      else
	      {
	        if (FLASH_IF_write_protection_config(FLASHIF_WRP_ENABLE) == FLASHIF_OK)
	        {
	        	serial_put_string((uint8_t *)"Write Protection enabled...\r\n");
	        	serial_put_string((uint8_t *)"System will now restart...\r\n");
	        }
	        else
	        {
	        	serial_put_string((uint8_t *)"Error: Flash write protection failed...\r\n");
	        }
	      }
	      break;
		default:
			serial_put_string((uint8_t *)"Invalid Number ! ==> The number should be either 1, 2, 3 or 4\r");
		break;
	    }
	  }



}


