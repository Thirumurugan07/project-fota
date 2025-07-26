#include "ymodem/flash_if.h"



uint32_t get_sector(uint32_t Address)
{
  if (Address < 0x08004000) return FLASH_SECTOR_0;
  else if (Address < 0x08008000) return FLASH_SECTOR_1;
  else if (Address < 0x0800C000) return FLASH_SECTOR_2;
  else if (Address < 0x08010000) return FLASH_SECTOR_3;
  else if (Address < 0x08020000) return FLASH_SECTOR_4;
  else if (Address < 0x08040000) return FLASH_SECTOR_5;
  else if (Address < 0x08060000) return FLASH_SECTOR_6;
  else if (Address < 0x08080000) return FLASH_SECTOR_7;
  else return FLASH_SECTOR_7; // fallback
}
/**
  * @brief  Unlocks Flash for write access
  * @param  None
  * @retval None
  */
void FLASH_IF_init(void) {
/* Unlocking hte program memroy*/
	if (HAL_FLASH_Unlock() != HAL_OK) {
		serial_put_string((uint8_t*)"Error occured while unlocking the flash operations\r\n");
	}

	// clearing the error flags before doing some flash operations
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_PGSERR | FLASH_FLAG_WRPERR | FLASH_FLAG_OPERR);


}

/**
  * @brief  This function does an erase of all user flash area
  * @param  start: start of user flash area
  * @retval FLASHIF_OK : user flash area successfully erased
  *         FLASHIF_ERASEKO : error occurred
  */

uint32_t FLASH_IF_erase(uint32_t StartSector) {
	FLASH_EraseInitTypeDef desc;
	uint32_t result = FLASHIF_OK;
	uint32_t sectorError;

	  /* Unlock the Flash to enable the flash control register access *************/
	FLASH_IF_init();


	desc.TypeErase = FLASH_TYPEERASE_SECTORS;
	desc.Sector = get_sector(StartSector);
	desc.NbSectors = 1;
	desc.Banks = FLASH_BANK_1;
	desc.VoltageRange = FLASH_VOLTAGE_RANGE_3;

	if (StartSector < USER_FLASH_END_ADDRESS) {

		if (HAL_FLASHEx_Erase(&desc, &sectorError) != HAL_OK) {
			char msg[50];
			sprintf(msg, "Erase failed at sector: %lu\n", sectorError);
			serial_put_string((uint8_t*)msg);
			result = FLASHIF_ERASEKO;
		}


	}
	else result = FLASHIF_ERASEKO;
	HAL_FLASH_Lock();
	return result;
}

/* Public functions ---------------------------------------------------------*/
/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  destination: start address for target location
  * @param  p_source: pointer on buffer with data to write
  * @param  length: length of data buffer (unit is 32-bit word)
  * @retval uint32_t 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */

uint32_t FLASH_IF_write(uint32_t destination, uint32_t* p_source, uint32_t length) {
	uint32_t status = FLASHIF_OK;
	int i = 0;

	HAL_FLASH_Unlock();

	for (i = 0; (i < length/2) && (destination <= USER_FLASH_END_ADDRESS - 8);i++) {


		/* Device voltage range supposed to be [2.7V to 3.6V], the operation will
		        be done by word */
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, destination, *((uint64_t*)(p_source+2*i))) == HAL_OK) {
			  /* Check the written value */

			if (*(uint64_t*)destination != *(uint64_t*)(p_source+2*i)) {
				 /* Flash content doesn't match SRAM content */
				status = FLASHIF_WRITINGCTRL_ERROR;
				break;
			}
			 /* Increment FLASH destination address */
			destination += 8;
		}

		else {
		       /* Error occurred while writing data in Flash memory */
			status = FLASHIF_WRITING_ERROR;
			break;
		}

	}
	return status;
}

/**
  * @brief  Returns the write protection status of application flash area.
  * @param  None
  * @retval If a sector in application area is write-protected returned value is a combination
            of the possible values : FLASHIF_PROTECTION_WRPENABLED, FLASHIF_PROTECTION_PCROPENABLED, ...
  *         If no sector is write-protected FLASHIF_PROTECTION_NONE is returned.
  */
uint32_t FLASH_IF_get_write_protection_status(void) {
	FLASH_OBProgramInitTypeDef config;
	uint32_t protected = FLASHIF_PROTECTION_NONE;
	 /* Get the current configuration */
	HAL_FLASHEx_OBGetConfig(&config);

	 /* Final evaluation of status */
	if ((config.WRPState == OB_WRPSTATE_ENABLE) && (config.WRPSector != 0)) {
		protected = FLASHIF_PROTECTION_WRPENABLED;
	}
	return protected;

}

/**
  * @brief  Configure the write protection status of user flash area.
  * @param  protectionstate : FLASHIF_WRP_DISABLE or FLASHIF_WRP_ENABLE the protection
  * @retval uint32_t FLASHIF_OK if change is applied.
  */

uint32_t FLASH_IF_write_protection_config(uint32_t protectionState) {

	FLASH_OBProgramInitTypeDef config;

	HAL_FLASH_Unlock();

	  /* Unlock the Options Bytes *************************************************/
	HAL_FLASH_OB_Unlock();

	  /* Get the current Option Bytes configuration */
	HAL_FLASHEx_OBGetConfig(&config);

	 config.OptionType = OPTIONBYTE_WRP;
	 config.Banks = FLASH_BANK_1;
	if (protectionState == FLASHIF_WRP_ENABLE) {
		config.WRPState = OB_WRPSTATE_ENABLE;
		config.WRPSector = (OB_WRP_SECTOR_5 | OB_WRP_SECTOR_6 | OB_WRP_SECTOR_7);
	}
	else {
		config.WRPState = OB_WRPSTATE_DISABLE;
	    // To disable protection, set WRPSector to 0x00 (no protection)
		config.WRPSector = (OB_WRP_SECTOR_5 | OB_WRP_SECTOR_6 | OB_WRP_SECTOR_7);
	}
	HAL_StatusTypeDef result;

	// Program Option Bytes
	    if (HAL_FLASHEx_OBProgram(&config) != HAL_OK) {
	        return FLASHIF_PROTECTION_ERROR;
	    }

	    // Launch the Option Bytes loading process
	    if (HAL_FLASH_OB_Launch() != HAL_OK) {
	        return FLASHIF_PROTECTION_ERROR;
	    }

	    HAL_FLASH_OB_Lock();
	    HAL_FLASH_Lock();
	return FLASHIF_OK;
}




















