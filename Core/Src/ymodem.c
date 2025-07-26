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
static void prepare_inital_packet(uint8_t* p_data, const uint8_t *p_file_name, uint32_t length);
static void prepare_packet(uint8_t *p_source, uint8_t *p_packet, uint8_t pkt_nr, uint32_t size_blk);
static HAL_StatusTypeDef receive_packet(uint8_t *p_data, uint32_t *p_length, uint32_t timeout);
uint16_t UpdateCRC16(uint16_t crc_in, uint8_t byte);
uint16_t Cal_CRC16(const uint8_t* p_data, uint32_t size);
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
	uint32_t crc;
	uint32_t packetSize = 0;
	HAL_StatusTypeDef status;
	uint8_t char1;
	*p_length = 0;

	status = HAL_UART_Receive(&UartHandle, &char1, 1, timeout);
	if (status == HAL_OK) {
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
		    if ((HAL_UART_Receive(&UartHandle, &char1, 1, timeout) == HAL_OK) && (char1 == CA))
			{
			  packetSize = 2;
			}
			else
			{
			  status = HAL_ERROR;
			}
			break;
		case ABORT1:
		case ABORT2:
			status = HAL_BUSY;
			break;
		default:
			status = HAL_ERROR;
			break;
		}
		*p_data = char1;
		if (packetSize >= PACKET_SIZE) {
			status = HAL_UART_Receive(&UartHandle, &p_data[PACKET_NUMBER_INDEX], (packetSize + PACKET_OVERHEAD_SIZE), timeout);
			if (status == HAL_OK) {
				if (p_data[PACKET_NUMBER_INDEX] != ((p_data[PACKET_CNUMBER_INDEX]) ^ NEGATIVE_BYTE)) {

					packetSize = 0;
					status = HAL_ERROR;
				}
				else {
					crc = p_data[packetSize + PACKET_DATA_INDEX] << 8;
					crc += p_data[packetSize + PACKET_DATA_INDEX + 1];
					if (HAL_CRC_Calculate(&CrcHandle, (uint32_t*)&p_data[PACKET_DATA_INDEX], packetSize) != crc )
					{
					            packetSize = 0;
					            status = HAL_ERROR;
					}
				}
			}
			else {
				packetSize = 0;
			}
		}
	}
	*p_length = packetSize;
	return status;
}

/**
  * @brief  Prepare the first block
  * @param  p_data:  output buffer
  * @param  p_file_name: name of the file to be sent
  * @param  length: length of the file to be sent in bytes
  * @retval None
  */

void prepare_inital_packet(uint8_t* p_data, const uint8_t* p_file_name, uint32_t length) {
	uint32_t i = 0, j = 0;
	uint8_t astring[10];

	/* First three bytes are constant---------------------------*/
	p_data[PACKET_START_INDEX] = SOH;
	p_data[PACKET_NUMBER_INDEX] = 0x00;
	p_data[PACKET_CNUMBER_INDEX] = 0xff;

	  /* Filename written */
	for (i = 0; (p_file_name[i] != '\0') && (i < FILE_NAME_LENGTH);i++) {
		p_data[i + PACKET_DATA_INDEX] = p_file_name[i];
	}
	p_data[i + PACKET_DATA_INDEX] = 0x00;

	  /* file size written */
	int_to_str(astring,length);
	i += 1 + PACKET_DATA_INDEX;
	while (astring[j] != 0) {
		p_data[i++] = astring[j++];
	}
	/* padding with zeros */
	  for (j = i; j < PACKET_SIZE + PACKET_DATA_INDEX; j++)
	  {
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

static void prepare_packet(uint8_t *p_source, uint8_t *p_packet, uint8_t pkt_nr, uint32_t size_blk) {
	uint8_t *p_record;
	uint32_t i, size, packetSize;

	  /* Make first three packet */
	packetSize = size_blk >= PACKET_1K_SIZE ? PACKET_1K_SIZE: PACKET_SIZE;
	size = size_blk < packetSize ? size_blk: packetSize;
	 if (packetSize == PACKET_1K_SIZE)
	  {
	    p_packet[PACKET_START_INDEX] = STX;
	  }
	  else
	  {
	    p_packet[PACKET_START_INDEX] = SOH;
	  }

	 p_packet[PACKET_NUMBER_INDEX] = pkt_nr;
	  p_packet[PACKET_CNUMBER_INDEX] = (~pkt_nr);
	  p_record = p_source;

	  /* Filename packet has valid data */
	  for (i = 0; (i < size + PACKET_DATA_INDEX);i++) {
		  p_packet[i] = *p_record;
	  }
	  if ( size  <= packetSize)
	   {
	     for (i = size + PACKET_DATA_INDEX; i < packetSize + PACKET_DATA_INDEX; i++)
	     {
	       p_packet[i] = 0x1A; /* EOF (0x1A) or 0x00 */
	     }
	   }
}

/**
  * @brief  Update CRC16 for input byte
  * @param  crc_in input value
  * @param  input byte
  * @retval None
  */
uint16_t UpdateCRC16(uint16_t crc_in, uint8_t byte)
{
  uint32_t crc = crc_in;
  uint32_t in = byte | 0x100;

  do
  {
    crc <<= 1;
    in <<= 1;
    if(in & 0x100)
      ++crc;
    if(crc & 0x10000)
      crc ^= 0x1021;
  }

  while(!(in & 0x10000));

  return crc & 0xffffu;
}

/**
  * @brief  Cal CRC16 for YModem Packet
  * @param  data
  * @param  length
  * @retval None
  */
uint16_t Cal_CRC16(const uint8_t* p_data, uint32_t size)
{
  uint32_t crc = 0;
  const uint8_t* dataEnd = p_data+size;

  while(p_data < dataEnd)
    crc = UpdateCRC16(crc, *p_data++);

  crc = UpdateCRC16(crc, 0);
  crc = UpdateCRC16(crc, 0);

  return crc&0xffffu;
}

/**
  * @brief  Calculate Check sum for YModem Packet
  * @param  p_data Pointer to input data
  * @param  size length of input data
  * @retval uint8_t checksum value
  */
uint8_t calc_checksum(const uint8_t *p_data, uint32_t size)
{
  uint32_t sum = 0;
  const uint8_t *p_data_end = p_data + size;

  while (p_data < p_data_end )
  {
    sum += *p_data++;
  }

  return (sum & 0xffu);
}

/* Public functions ---------------------------------------------------------*/
/**
  * @brief  Receive a file using the ymodem protocol with CRC16.
  * @param  p_size The size of the file.
  * @retval COM_StatusTypeDef result of reception/programming
  */
COM_StatusTypeDef ymodem_receive ( uint32_t *p_size ) {

		uint32_t flashDestination, ramSource, fileSize;
		uint32_t i, packetLength, sessionDone = 0, fileDone, sessionBegin= 0, errors = 0;
		uint8_t* filePtr;
		uint8_t p_fileSize[FILE_SIZE_LENGTH], tmp, packetsReceived;
		COM_StatusTypeDef result = COM_OK;
	 /* Initialize flashdestination variable */
		flashDestination = APPLICATION_ADDRESS;
		while ((sessionDone == 0) && (result == COM_OK)) {
			packetsReceived = 0;
			fileDone = 0;
			while ((fileDone == 0) && (result == COM_OK)) {
				switch (receive_packet(aPacketData, &packetLength, DOWNLOAD_TIMEOUT)) {
				case HAL_OK:
					errors = 0;
					switch(packetLength) {
					case 2:
						/* Abort by the user--------------*/
						serial_put_byte(ACK);
						result = COM_ABORT;
						break;

					case 0:
						/* End of transmission-----------*/
						serial_put_byte(ACK);
						fileDone = 1;
						break;
					default:
						/* Normal Data range-------------------*/
						if (aPacketData[PACKET_NUMBER_INDEX] != packetsReceived) {
							serial_put_byte(NAK);
						}
						else {
							if (packetsReceived == 0) {
								/* File Name Packet--------------*/
								if (aPacketData[PACKET_DATA_INDEX] != 0) {
									filePtr = aPacketData + PACKET_DATA_INDEX;
									i = 0;
									while ((*filePtr != 0) && (i < FILE_NAME_LENGTH)) {
										aFileName[i++] = *filePtr++;
									}
				                    /* File size extraction */
									aFileName[i++] = '\0';
									i = 0;
									filePtr++;

									while ((*filePtr != ' ') && (i < FILE_SIZE_LENGTH)) {
										p_fileSize[i++] = *filePtr++;
									}
									p_fileSize[i++] = '\0';
									str_to_int(p_fileSize, &fileSize);

									 /* Test the size of the image to be sent */
									 /* Image size is greater than Flash size */
									if (*p_size > (USER_FLASH_SIZE + 1)) {
									 /* End session */
									  tmp = CA;
									  HAL_UART_Transmit(&UartHandle, &tmp, 1, NAK_TIMEOUT);
									  HAL_UART_Transmit(&UartHandle, &tmp, 1, NAK_TIMEOUT);
									  result = COM_LIMIT;
									}
									/* erase user application area */
									FLASH_IF_erase(APPLICATION_ADDRESS);
									*p_size = fileSize;
									serial_put_byte(ACK);
									serial_put_byte(CRC16);
								}

				                /* File header packet is empty, end session */
								else {
									serial_put_byte(ACK);
									fileDone = 1;
									sessionDone = 1;
									break;
								}
							}
							else /* Data packet received */
							{
								ramSource = (uint32_t) & aPacketData[PACKET_DATA_INDEX];
								 /* Write received data in Flash */
								if (FLASH_IF_write(flashDestination, (uint32_t*)ramSource,packetLength/4)  == FLASHIF_OK) {
									flashDestination += packetLength;
								}
								else /* An error occurred while writing to Flash memory */
								{
									/* End session */
									serial_put_byte(CA);
									serial_put_byte(CA);
									result = COM_DATA;
								}
							}
							packetsReceived ++;
							sessionBegin = 1;
						}
						break;
				}
					break;
				case HAL_BUSY: /* Abort actually */
					serial_put_byte(CA);
					serial_put_byte(CA);
					result = COM_ABORT;
					break;
				default:
					if (sessionBegin) {
						errors++;
					}
					if (errors > MAX_ERRORS) {
						  /* Abort communication */
						serial_put_byte(CA);
						serial_put_byte(CA);
						result = COM_ABORT;
					}
					else {
						serial_put_byte(CRC16); /* Ask for a packet */
						serial_put_byte(ACK); //BFM
					}
					break;
				}
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
COM_StatusTypeDef ymodem_transmit(uint8_t* p_buff,const uint8_t* p_file_name, uint32_t file_size)
{
	  uint32_t errors = 0, ackRecpt = 0, size = 0, pktSize;
	  uint8_t *p_buf_int;
	  COM_StatusTypeDef result = COM_OK;
	  uint32_t blkNumber = 1;
	  uint8_t aRxCtrl[2];
	  uint8_t i;
	  #ifdef CRC16_F
	  uint32_t tempCrc;
	  #else /* CRC16_F */
	  uint8_t tempChkSum;
	  #endif /* CRC16_F */

	  /* Prepare first block - header */
	  prepare_inital_packet(aPacketData, p_file_name, file_size);

	  while ((ackRecpt != 0) && (result == COM_OK)) {
		  /* Send Packet */
		  HAL_UART_Transmit(&UartHandle, &aPacketData[PACKET_START_INDEX], PACKET_SIZE + PACKET_HEADER_SIZE, NAK_TIMEOUT);
		  /* Send CRC or Check Sum based on CRC16_F */
		 #ifdef CRC16_F
		     tempCrc = HAL_CRC_Calculate(&CrcHandle, (uint32_t*)&aPacketData[PACKET_DATA_INDEX], PACKET_SIZE);
		     serial_put_byte(tempCrc >> 8);
		     serial_put_byte((tempCrc & 0xFF));
		 #else /* CRC16_F */
		     tempChksum = CalcChecksum(&aPacketData[PACKET_DATA_INDEX], PACKET_SIZE);
		     serial_put_byte(tempChksum);
		#endif /* CRC16_F */

		     /* Wait for Ack and 'C' */
		        if (HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK)
		        {
		          if (aRxCtrl[0] == ACK)
		          {
		            ackRecpt = 1;
 		            HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT); //BFM added to wait for the 'C'
		          }
		          else if (aRxCtrl[0] == CA)
		          {
		            if ((HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK) && (aRxCtrl[0] == CA))
		            {
		              HAL_Delay(2);
		              __HAL_UART_FLUSH_DRREGISTER(&UartHandle);
		              __HAL_UART_CLEAR_OREFLAG(&UartHandle);
		              result = COM_ABORT;
		            }
		          }
		        }
		        else
		        {
		          errors++;
		        }
		        if (errors >= MAX_ERRORS)
		         {
		             result = COM_ERROR;
		         }
	  }
		        p_buf_int = p_buff;
		        size = file_size;

		        /* Here 1024 bytes length is used to send the packets */
		        while ((size) && (result == COM_OK)) {
		        	prepare_packet(p_buf_int, aPacketData, blkNumber, size);
		        	ackRecpt = 0;
		        	aRxCtrl[0] = 0;
		        	errors = 0;

		        	    /* Resend packet if NAK for few times else end of communication */

		        	while ((!ackRecpt) && (result == COM_OK)) {
		        		/* Send next packet */
		        		      if (size >= PACKET_1K_SIZE)
		        		      {
		        		        pktSize = PACKET_1K_SIZE;
		        		      }
		        		      else
		        		      {
		        		        pktSize = PACKET_SIZE;
		        		      }
		        		      HAL_UART_Transmit(&UartHandle,&aPacketData[PACKET_START_INDEX], pktSize + PACKET_HEADER_SIZE, NAK_TIMEOUT);
		        		      /* Send CRC or Check Sum based on CRC16_F */
		        		#ifdef CRC16_F
		        		      tempCrc = HAL_CRC_Calculate(&CrcHandle, (uint32_t*)&aPacketData[PACKET_DATA_INDEX], pktSize);
		        		      serial_put_byte(tempCrc >> 8);
		        		      serial_put_byte(tempCrc & 0xFF);
		        		#else /* CRC16_F */
		        		      tempChksum = CalcChecksum(&aPacketData[PACKET_DATA_INDEX], pktSize);
		        		      serial_put_byte(tempChksum);
		        		#endif /* CRC16_F */
		        		      /* Wait for Ack */
		        		      if (HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK && (aRxCtrl[0] == ACK))
		        		      {
									ackRecpt = 1;
									if (size >= pktSize) {
										p_buf_int += pktSize;
										size -= pktSize;
										if (blkNumber == (USER_FLASH_SIZE / PACKET_1K_SIZE))
										  {
											result = COM_LIMIT; /* boundary error */
										  }
										  else
										  {
											blkNumber++;
										  }
									}
									else
									{
										size = 0;
										p_buf_int += pktSize;
									}
		        		      }
		        		      else {
		        		    	  errors++;
		        		      }
		        		      /* Resend packet if NAK  for a count of 10 else end of communication */
		        		      if (errors >= MAX_ERRORS)
		        		      {
		        		        result = COM_ERROR;
		        		      }
		        	}

		        }
		        /* Sending End Of Transmission char */
			  ackRecpt = 0;
			  aRxCtrl[0] = 0x00;
			  errors = 0;
			  while (( !ackRecpt ) && ( result == COM_OK ))
			    {
			      serial_put_byte(EOT);

			      /* Wait for Ack */
			      if (HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK)
					{
					  if (aRxCtrl[0] == ACK)
					  {
						ackRecpt = 1;
						HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT); //BFM added to wait for the 'C'
					  }
					  else if (aRxCtrl[0] == CA)
					  {
						if ((HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK) && (aRxCtrl[0] == CA))
						{
						  HAL_Delay(2);
						  __HAL_UART_FLUSH_DRREGISTER(&UartHandle);
						  __HAL_UART_CLEAR_OREFLAG(&UartHandle);
						  result = COM_ABORT;
						}
					  }
					}
			      else
			      {
			        errors++;
			      }

			      if (errors >=  MAX_ERRORS)
			      {
			        result = COM_ERROR;
			      }
			    }

			  /* Empty packet sent - some terminal emulators need this to close session */
			  if ( result == COM_OK )
			   {
			      /* Preparing an empty packet */
			      aPacketData[PACKET_START_INDEX] = SOH;
			      aPacketData[PACKET_NUMBER_INDEX] = 0;
			      aPacketData[PACKET_CNUMBER_INDEX] = 0xFF;
			      for (i = PACKET_DATA_INDEX; i < (PACKET_SIZE + PACKET_DATA_INDEX); i++)
			      {
			        aPacketData [i] = 0x00;
			      }

			      /* Send Packet */
			      HAL_UART_Transmit(&UartHandle, &aPacketData[PACKET_START_INDEX], PACKET_SIZE + PACKET_HEADER_SIZE, NAK_TIMEOUT);

			      /* Send CRC or Check Sum based on CRC16_F */
					#ifdef CRC16_F
						  tempCrc = HAL_CRC_Calculate(&CrcHandle, (uint32_t*)&aPacketData[PACKET_DATA_INDEX], pktSize);
						  serial_put_byte(tempCrc >> 8);
						  serial_put_byte(tempCrc & 0xFF);
					#else /* CRC16_F */
						  tempChksum = CalcChecksum(&aPacketData[PACKET_DATA_INDEX], pktSize);
						  serial_put_byte(tempChksum);
					#endif /* CRC16_F */

			      /* Wait for Ack and 'C' */
			      if (HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK)
			      {
			    	  if (aRxCtrl[0] == CA)
					  {
						if ((HAL_UART_Receive(&UartHandle, &aRxCtrl[0], 1, NAK_TIMEOUT) == HAL_OK) && (aRxCtrl[0] == CA))
						{
						  HAL_Delay(2);
						  __HAL_UART_FLUSH_DRREGISTER(&UartHandle);
						  __HAL_UART_CLEAR_OREFLAG(&UartHandle);
						  result = COM_ABORT;
						}
					  }
			      }
			    }
			    return result; /* file transmitted successfully */
}















































