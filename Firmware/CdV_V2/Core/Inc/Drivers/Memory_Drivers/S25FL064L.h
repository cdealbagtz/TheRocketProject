/*
 * S25FL064L.h
 *
 *  Created on: Sep 29, 2025
 *      Author: cdealba
 */

#ifndef INC_DRIVER_LAYER_S25FL064L_H_
#define INC_DRIVER_LAYER_S25FL064L_H_

#include "main.h"
#include "GPIO.h"
#include "SPI.h"



#define Flash_MaxWaitTime 20
#define hflash hspi1

uint32_t S25FL064_ID(void);
HAL_StatusTypeDef S25FL064_init(void);
void S25FL064_Read(uint32_t adress,uint32_t size,uint8_t *rcv);
void S25FL064_Write(uint16_t Page,uint8_t *Data);
void S25FL064_Erase(uint16_t sector);
void S25FL064_chipErase(void);

void resetFlash(void);

void checkflashstatus(void);

#endif /* INC_DRIVER_LAYER_S25FL064L_H_ */
