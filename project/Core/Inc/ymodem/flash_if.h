
#ifndef __FLASH_IF_H
#define __FLASH_IF_H

#include "stm32f4xx_hal.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/


/* Error codes */
enum {
	FLASHIF_OK	=	0,
	FLASHIF_ERASEKO,
	FLASHIF_WRITINGCTRL_ERROR,
	FLASHIF_WRITING_ERROR,
	FLASHIF_PROTECTION_ERROR,
	FLASHIF_PARAM_ERROR
};

/* protection types */
enum {
	FLASHIF_PROTECTION_NONE			=	0x00,
	FLASHIF_PROTECTION_PCROPENABLED	=	0x01,
	FLASHIF_PROTECTION_WRPENABLED	=	0x02,
	FLASHIF_PROTECTION_RDPENABLED	=	0x04,
};

/* protection update */
enum {
	FLASHIF_WRP_ENABLE,
	FLASHIF_WRP_DISABLE
};

/* Define the address from where user application will be loaded.
   Note: this area is reserved for the IAP code                  */

//#define FLASH_PAGE_STEP         FLASH_PAGE_SIZE           /* Size of page : 2 Kbytes */
#define APPLICATION_ADDRESS     (uint32_t)0x08020000      /* Start user code address: ADDR_FLASH_PAGE_64 */


#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, Bank1, 128 Kbyte */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, Bank1, 128 Kbyte */
#define ADDR_FLASH_SECTOR_2   	((uint32_t)0x08008000) /* Base @ of Sector 2, Bank1, 128 Kbyte */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, Bank1, 128 Kbyte */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, Bank1, 128 Kbyte */
#define ADDR_FLASH_SECTOR_5    	((uint32_t)0x08020000) /* Base @ of Sector 5, Bank1, 128 Kbyte */
#define ADDR_FLASH_SECTOR_6  	((uint32_t)0x08040000) /* Base @ of Sector 6, Bank1, 128 Kbyte */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, Bank1, 128 Kbyte */
/* Notable Flash addresses */
#define FLASH_START		              ((uint32_t)0x08000000)
#define USER_FLASH_START_ADDRESS      ((uint32_t)0x08020000)
#define USER_FLASH_END_ADDRESS        ((uint32_t)(0x0807FFFF ))
#define USER_FLASH_SIZE   (USER_FLASH_END_ADDRESS - USER_FLASH_START_ADDRESS + 1)  // 384 KB
#define FLASH_SECTOR_TO_BE_PROTECTED (OB_WRP_SECTOR_5 | OB_WRP_SECTOR_6 | OB_WRP_SECTOR_7)
#define START_OF_RAM    ((uint8_t)0)
#define END_OF_RAM      ((uint8_t)63)

/* Exported macro ------------------------------------------------------------*/
/* absolute value */
#define ABS_RETURN(x,y)               (((x) < (y)) ? (y) : (x))


/* Get the number of sectors from where the user program will be loaded */
#define FLASH_SECTOR_NUMBER get_sector(USER_FLASH_START_ADDRESS)

/* Exported functions ------------------------------------------------------- */
uint32_t get_sector(uint32_t Address);

void FLASH_IF_init(void);
uint32_t FLASH_IF_erase(uint32_t StartSector);
uint32_t FLASH_IF_write(uint32_t destination, uint32_t* p_source, uint32_t length);
uint32_t FLASH_IF_get_write_protection_status(void);
uint32_t FLASH_IF_write_protection_config(uint32_t protectionState);
void FLASH_IF_disable_all_protection(void);

#endif
























