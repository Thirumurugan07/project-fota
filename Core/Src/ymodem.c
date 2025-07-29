/*
 * ymodem.c
 *
 *  Created on: 24 July 2025
 *      Author: Thirumurugan S
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ymodem/menu.h"
#include "ymodem/ymodem.h"
#include "ymodem/flash_if.h"
#include "ymodem/common.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CRC16_F       /* activate the CRC16 integrity */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* @note ATTENTION - please keep this variable 32bit alligned */
uint8_t aPacketData[PACKET_1K_SIZE + PACKET_DATA_INDEX + PACKET_TRAILER_SIZE];

/* Private function prototypes -----------------------------------------------*/
static void prepare_initial_packet(uint8_t* p_data, const uint8_t *p_file_name, uint32_t length);
static void prepare_packet(uint8_t *p_source, uint8_t *p_packet, uint8_t pkt_nr, uint32_t size_blk);
static HAL_StatusTypeDef receive_packet(uint8_t *p_data, uint32_t *p_length, uint32_t timeout);
uint16_t UpdateCRC16(uint16_t crc_in, uint8_t byte);
uint16_t calc_crc16(const uint8_t* p_data, uint32_t size);
uint8_t CalcChecksum(const uint8_t *p_data, uint32_t size);

/**
  * @brief  Receive a packet from sender
  * @param  data
  * @param  length
  *     0: end of transmission
  *     2: abort by sender
  *    >0: packet length
  * @param  timeout
  * @retval HAL_OK: normally return
  *         HAL_BUSY: abort by user
  */

static HAL_StatusTypeDef receive_packet(uint8_t *p_data, uint32_t *p_length, uint32_t timeout) {
    uint16_t crc;
    uint32_t packetSize = 0;
    HAL_StatusTypeDef status;
    uint8_t char1;

    *p_length = 0;
    status = HAL_UART_Receive(&UartHandle, &char1, 1, timeout);

    if (status != HAL_OK) {
        return status;
    }

    switch(char1) {
        case SOH:
            packetSize = PACKET_SIZE;
            break;
        case STX:
            packetSize = PACKET_1K_SIZE;
            break;
        case EOT:
        	break;

        case CA:
            if ((HAL_UART_Receive(&UartHandle, &char1, 1, timeout) != HAL_OK) || (char1 != CA)) {
                return HAL_ERROR;
            }
            packetSize = 2;
            break;
        case ABORT1:
        case ABORT2:
            return HAL_BUSY;
        default:
            return HAL_ERROR;
    }

    *p_data = char1;

    if (packetSize >= PACKET_SIZE) {
        status = HAL_UART_Receive(&UartHandle,
                                &p_data[PACKET_NUMBER_INDEX],
                                (packetSize + PACKET_OVERHEAD_SIZE),
                                timeout);

        if (status != HAL_OK) {
            *p_length = 0;
            return status;
        }

        /* Validate packet sequence numbers */
        if (p_data[PACKET_NUMBER_INDEX] != ((p_data[PACKET_CNUMBER_INDEX]) ^ NEGATIVE_BYTE)) {
            *p_length = 0;
            return HAL_ERROR;
        }

        /* Check CRC */
        crc = (p_data[packetSize + PACKET_DATA_INDEX] << 8) |
               p_data[packetSize + PACKET_DATA_INDEX + 1];

        if (calc_crc16(&p_data[PACKET_DATA_INDEX], packetSize) != crc )
                  {
                    packetSize = 0;
                    status = HAL_ERROR;
                  }
    }
    else packetSize = 0;

    *p_length = packetSize;
    return HAL_OK;
}

/**
  * @brief  Prepare the first block
  * @param  p_data:  output buffer
  * @param  p_file_name: name of the file to be sent
  * @param  length: length of the file to be sent in bytes
  * @retval None
  */

static void prepare_initial_packet(uint8_t* p_data, const uint8_t* p_file_name, uint32_t length) {
    uint32_t i = 0, j = 0;
    uint8_t aString[10];  // camelCase for non-pointers

    /* First three bytes are constant */
    p_data[PACKET_START_INDEX] = SOH;
    p_data[PACKET_NUMBER_INDEX] = 0x00;
    p_data[PACKET_CNUMBER_INDEX] = 0xff;

    /* Filename written */
    for (i = 0; (p_file_name[i] != '\0') && (i < FILE_NAME_LENGTH); i++) {
        p_data[i + PACKET_DATA_INDEX] = p_file_name[i];
    }
    p_data[i + PACKET_DATA_INDEX] = 0x00;

    /* File size written */
    int_to_str(aString, length);  // Assuming `int_to_str` is your function
    i += 1 + PACKET_DATA_INDEX;
    while (aString[j] != '\0') {
        p_data[i++] = aString[j++];
    }

    /* Padding with zeros */
    for (j = i; j < PACKET_SIZE + PACKET_DATA_INDEX; j++) {
        p_data[j] = 0;
    }
}

/**
  * @brief  Prepare the data packet
  * @param  p_source: pointer to the data to be sent
  * @param  p_packet: pointer to the output buffer
  * @param  pkt_nr: number of the packet
  * @param  size_blk: length of the block to be sent in bytes
  * @retval None
  */

void prepare_packet(uint8_t* p_source, uint8_t* p_packet, uint8_t pktNr, uint32_t sizeBlk) {
    uint8_t* p_record;  // Pointer: p_ prefix + snake_case
    uint32_t i, size, packetSize;  // camelCase for non-pointers

    /* Determine packet size (1K or normal) */
    packetSize = (sizeBlk >= PACKET_1K_SIZE) ? PACKET_1K_SIZE : PACKET_SIZE;
    size = (sizeBlk < packetSize) ? sizeBlk : packetSize;

    /* Set packet header */
    p_packet[PACKET_START_INDEX] = (packetSize == PACKET_1K_SIZE) ? STX : SOH;
    p_packet[PACKET_NUMBER_INDEX] = pktNr;
    p_packet[PACKET_CNUMBER_INDEX] = ~pktNr;

    /* Copy data into packet */
    p_record = p_source;
    for (i = PACKET_DATA_INDEX; i < size + PACKET_DATA_INDEX; i++) {
        p_packet[i] = *p_record++;
    }

    /* Pad remaining space with EOF (0x1A) */
    if (size <= packetSize) {
        for (i = size + PACKET_DATA_INDEX; i < packetSize + PACKET_DATA_INDEX; i++) {
            p_packet[i] = 0x1A;  // EOF marker
        }
    }
}

/**
  * @brief  Update CRC16 for input byte
  * @param  crc_in input value
  * @param  input byte
  * @retval None
  */
uint16_t update_crc16(uint16_t crcIn, uint8_t byte) {
    uint32_t crc = crcIn;
    uint32_t in = byte | 0x100;

    do {
        crc <<= 1;
        in <<= 1;
        if (in & 0x100)
            ++crc;
        if (crc & 0x10000)
            crc ^= 0x1021;
    } while (!(in & 0x10000));

    return crc & 0xFFFFu;
}

/**
  * @brief  Cal CRC16 for YModem Packet
  * @param  data
  * @param  length
  * @retval None
  */
uint16_t calc_crc16(const uint8_t* p_data, uint32_t size) {
	uint32_t crc = 0;
	const uint8_t* p_data_end = p_data + size;

	while (p_data < p_data_end)
		crc = update_crc16(crc, *p_data++);

	crc = update_crc16(crc, 0);
	crc = update_crc16(crc, 0);

	return crc & 0xFFFFu;
}

/**
* @brief  Calculate Check sum for YModem Packet
* @param  p_data Pointer to input data
* @param  size length of input data
* @retval uint8_t checksum value
*/
uint8_t calc_checksum(const uint8_t* p_data, uint32_t size) {
	uint32_t sum = 0;
	const uint8_t* p_data_end = p_data + size;

	while (p_data < p_data_end) {
		sum += *p_data++;
	}

	return (sum & 0xFFu);
}

/* Public functions ---------------------------------------------------------*/
/**
  * @brief  Receive a file using the ymodem protocol with CRC16.
  * @param  p_size The size of the file.
  * @retval COM_StatusTypeDef result of reception/programming
  */
COM_StatusTypeDef ymodem_receive(uint32_t* p_size) {
	 	 	 HAL_FLASH_Unlock();
			 HAL_FLASH_OB_Unlock();
			  FLASH_OBProgramInitTypeDef config;
			  HAL_FLASHEx_OBGetConfig(&config);
			 config.OptionType = OPTIONBYTE_WRP;
			 config.WRPState= OB_WRPSTATE_DISABLE;
			 config.RDPLevel = OB_RDP_LEVEL0;
			  config.WRPSector = (OB_WRP_SECTOR_5 | OB_WRP_SECTOR_6 | OB_WRP_SECTOR_7);
			  if (HAL_FLASHEx_OBProgram(&config) == HAL_OK)
			  {
			      HAL_FLASH_OB_Launch(); // This will cause a reset!
			  }

			  HAL_FLASH_OB_Lock();
			  HAL_FLASH_Lock();

    uint32_t flashDestination, ramSource, fileSize;
    uint32_t i, packetLength, sessionDone = 0, fileDone, sessionBegin = 0, errors = 0;
    uint8_t* p_filePtr;
    uint8_t p_fileSize[FILE_SIZE_LENGTH], tmp, packetsReceived;
    COM_StatusTypeDef result = COM_OK;

    flashDestination = APPLICATION_ADDRESS;

    while ((sessionDone == 0) && (result == COM_OK)) {
        packetsReceived = 0;
        fileDone = 0;
        while ((fileDone == 0) && (result == COM_OK)) {
            switch (receive_packet(aPacketData, &packetLength, DOWNLOAD_TIMEOUT)) {
                case HAL_OK:
                    errors = 0;
                    switch (packetLength) {
                        case 2:
                            serial_put_byte(ACK);
                            result = COM_ABORT;
                            break;

                        case 0:
                            serial_put_byte(ACK);
                            fileDone = 1;
                            break;

                        default:
                            if (aPacketData[PACKET_NUMBER_INDEX] != (packetsReceived & 0xffU)) {
                                serial_put_byte(NAK);
                            }
                            else {
                                if (packetsReceived == 0) {
                                    if (aPacketData[PACKET_DATA_INDEX] != 0) {
                                        p_filePtr = aPacketData + PACKET_DATA_INDEX;
                                        i = 0;
                                        while ((*p_filePtr != 0) && (i < FILE_NAME_LENGTH)) {
                                            aFileName[i++] = *p_filePtr++;
                                        }
                                        aFileName[i++] = '\0';

                                        i = 0;
                                        p_filePtr++;
                                        while ((*p_filePtr != ' ') && (i < FILE_SIZE_LENGTH)) {
                                            p_fileSize[i++] = *p_filePtr++;
                                        }
                                        p_fileSize[i++] = '\0';
                                        str_to_int(p_fileSize, &fileSize);

                                        if (fileSize > (USER_FLASH_SIZE + 1)) {

                                            tmp = CA;
                                            HAL_UART_Transmit(&UartHandle, &tmp, 1, NAK_TIMEOUT);
                                            HAL_UART_Transmit(&UartHandle, &tmp, 1, NAK_TIMEOUT);
                                            result = COM_LIMIT;
                                            break;
                                        }
                                        FLASH_IF_disable_all_protection();
                                        if (FLASH_IF_erase(APPLICATION_ADDRESS) != FLASHIF_OK) {
                                           // serial_put_string((uint8_t*)"[ERROR] Flash erase failed\r\n");
                                            return COM_ERROR;
                                        }

                                        *p_size = fileSize;
                                        serial_put_byte(ACK);
                                        serial_put_byte(CRC16);
                                    }
                                    else {
                                        serial_put_byte(ACK);
                                        fileDone = 1;
                                        sessionDone = 1;
                                        break;
                                    }
                                }
                                else {
                                	ramSource = (uint32_t)&aPacketData[PACKET_DATA_INDEX];

                                	// Check if the source pointer is non-null and in RAM
                                	if (ramSource == 0 || ramSource < 0x20000000 || ramSource > 0x2004FFFF) {
                                	    // Invalid pointer or not in SRAM range for STM32F4 (adjust if needed)
                                	    serial_put_byte(CA);
                                	    serial_put_byte(CA);
                                	    result = FLASHIF_WRITING_ERROR;

                                	} else {
                                	    uint32_t stt = FLASH_IF_write(flashDestination, (uint32_t*)ramSource, packetLength / 4);

                                	    if (stt == FLASHIF_WRITING_ERROR) {
                                	        serial_put_byte(CA);
                                	        serial_put_byte(CA);
                                	        result = FLASHIF_WRITING_ERROR;

                                	    }
                                	    else if (stt == FLASHIF_WRITINGCTRL_ERROR) {
                                	        serial_put_byte(CA);
                                	        serial_put_byte(CA);
                                	        result = FLASHIF_WRITINGCTRL_ERROR;
                                	    }
                                	    else {
                                	        flashDestination += packetLength;
                                	        serial_put_byte(ACK);
                                	    }
                                	}
                                }
                                packetsReceived++;
                                sessionBegin = 1;
                            }
                            break;
                    }
                    break;

                case HAL_BUSY:

                    serial_put_byte(CA);
                    serial_put_byte(CA);
                    result = COM_ABORT;
                    break;

                default:
                    if (sessionBegin) {
                        errors++;
                    }
                    if (errors > MAX_ERRORS) {

                        serial_put_byte(CA);
                        serial_put_byte(CA);
                        result = COM_ABORT;
                    }
                    else {
                        serial_put_byte(CRC16);
                    }
                    break;
            }
        }
    }
    HAL_Delay(5000);
    /* Final status report */
    if (result == COM_OK) {
        serial_put_string((uint8_t*)"\r\nYMODEM Success: ");
        serial_put_string(aFileName);

        serial_put_string((uint8_t*)p_fileSize);
    }
    else {
        serial_put_string((uint8_t*)"\r\nYMODEM Failed: ");
        switch(result) {
            case COM_LIMIT:
                serial_put_string((uint8_t*)"File too large");
                break;
            case COM_DATA:
                serial_put_string((uint8_t*)"Flash write error");
                break;

            case COM_ABORT:
                serial_put_string((uint8_t*)"Transfer aborted");
                break;
            default:
                serial_put_string((uint8_t*)"Unknown error");\
                break;
        }
    }

    return result;
}
/**
  * @brief  Transmit a file using the ymodem protocol
  * @param  p_buff: Address of the first byte
  * @param  p_file_name: Name of the file sent
  * @param  file_size: Size of the transmission
  * @retval COM_StatusTypeDef result of the communication
  */
COM_StatusTypeDef ymodem_transmit(uint8_t* p_buf, const uint8_t* p_file_name, uint32_t file_size) {
    uint32_t errors = 0, ackRecpt = 0, size = 0, pktSize;
    uint8_t *p_buf_int;
    COM_StatusTypeDef result = COM_OK;
    uint32_t blkNumber = 1;
    uint8_t aRxCtrl[2];
    uint8_t i;
#ifdef CRC16_F
    uint32_t tempCrc;
#else
    uint8_t tempChkSum;
#endif

    /* Prepare first block - header */
    prepare_initial_packet(aPacketData, p_file_name, file_size);

    while ((!ackRecpt) && (result == COM_OK)) {
        /* Send Packet */
        HAL_UART_Transmit(&UartHandle, &aPacketData[PACKET_START_INDEX], PACKET_SIZE + PACKET_HEADER_SIZE, NAK_TIMEOUT);

        /* Send CRC or Checksum */
#ifdef CRC16_F
        tempCrc = HAL_CRC_Calculate(&CrcHandle, (uint32_t*)&aPacketData[PACKET_DATA_INDEX], PACKET_SIZE);
        serial_put_byte(tempCrc >> 8);
        serial_put_byte(tempCrc & 0xFF);
#else
        tempChkSum = calc_checksum(&aPacketData[PACKET_DATA_INDEX], PACKET_SIZE);
        Serial_PutByte(tempChkSum);
#endif

        /* Wait for response */
        if (HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK) {
            if (aRxCtrl[0] == ACK) {
                ackRecpt = 1;
                HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT); // Wait for 'C'
            }
            else if (aRxCtrl[0] == CA) {
                if ((HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK) && (aRxCtrl[0] == CA)) {
                    HAL_Delay(2);
                    __HAL_UART_FLUSH_DRREGISTER(&UartHandle);
                    result = COM_ABORT;
                }
            }
        }
        else {
            errors++;
        }

        if (errors >= MAX_ERRORS) {
            result = COM_ERROR;
        }
    }

    p_buf_int = p_buf;
    size = file_size;

    /* Send data packets */
    while ((size) && (result == COM_OK)) {
        prepare_packet(p_buf_int, aPacketData, blkNumber, size);
        ackRecpt = 0;
        errors = 0;

        while ((!ackRecpt) && (result == COM_OK)) {
            /* Determine packet size */
            pktSize = (size >= PACKET_1K_SIZE) ? PACKET_1K_SIZE : PACKET_SIZE;

            /* Send packet */
            HAL_UART_Transmit(&UartHandle, &aPacketData[PACKET_START_INDEX], pktSize + PACKET_HEADER_SIZE, NAK_TIMEOUT);

            /* Send CRC/Checksum */
#ifdef CRC16_F
            tempCrc = HAL_CRC_Calculate(&CrcHandle, (uint32_t*)&aPacketData[PACKET_DATA_INDEX], pktSize);
            serial_put_byte(tempCrc >> 8);
            serial_put_byte(tempCrc & 0xFF);
#else
            tempChkSum = calc_checksum(&aPacketData[PACKET_DATA_INDEX], pktSize);
            Serial_PutByte(tempChkSum);
#endif

            /* Wait for ACK */
            if ((HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK) && (aRxCtrl[0] == ACK)) {
                ackRecpt = 1;
                if (size > pktSize) {
                    p_buf_int += pktSize;
                    size -= pktSize;
                    if (blkNumber == (USER_FLASH_SIZE / PACKET_1K_SIZE)) {
                        result = COM_LIMIT;
                    } else {
                        blkNumber++;
                    }
                }
                else {
                    p_buf_int += pktSize;
                    size = 0;
                }
            }
            else {
                errors++;
            }

            if (errors >= MAX_ERRORS) {
                result = COM_ERROR;
            }
        }
    }

    /* Send EOT */
    if (result == COM_OK) {
        ackRecpt = 0;
        errors = 0;
        while ((!ackRecpt) && (result == COM_OK)) {
            serial_put_byte(EOT);

            if (HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK) {
                if (aRxCtrl[0] == ACK) {
                    ackRecpt = 1;
                }
                else if (aRxCtrl[0] == CA) {
                    if ((HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK) && (aRxCtrl[0] == CA)) {
                        HAL_Delay(2);
                        __HAL_UART_FLUSH_DRREGISTER(&UartHandle);
                        result = COM_ABORT;
                    }
                }
            }
            else {
                errors++;
            }

            if (errors >= MAX_ERRORS) {
                result = COM_ERROR;
            }
        }
    }

    /* Send empty packet to close session */
    if (result == COM_OK) {
        aPacketData[PACKET_START_INDEX] = SOH;
        aPacketData[PACKET_NUMBER_INDEX] = 0;
        aPacketData[PACKET_CNUMBER_INDEX] = 0xFF;
        for (i = PACKET_DATA_INDEX; i < (PACKET_SIZE + PACKET_DATA_INDEX); i++) {
            aPacketData[i] = 0x00;
        }

        HAL_UART_Transmit(&UartHandle, &aPacketData[PACKET_START_INDEX], PACKET_SIZE + PACKET_HEADER_SIZE, NAK_TIMEOUT);

#ifdef CRC16_F
        tempCrc = HAL_CRC_Calculate(&CrcHandle, (uint32_t*)&aPacketData[PACKET_DATA_INDEX], PACKET_SIZE);
        serial_put_byte(tempCrc >> 8);
        serial_put_byte(tempCrc & 0xFF);
#else
        tempChkSum = calc_checksum(&aPacketData[PACKET_DATA_INDEX], PACKET_SIZE);
        Serial_PutByte(tempChkSum);
#endif

        if (HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK) {
            if (aRxCtrl[0] == CA) {
                HAL_Delay(2);
                __HAL_UART_FLUSH_DRREGISTER(&UartHandle);
                result = COM_ABORT;
            }
        }
    }

    return result;
}
