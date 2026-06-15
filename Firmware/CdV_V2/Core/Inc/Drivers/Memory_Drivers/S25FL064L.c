/*
 * S25FL064L.c
 *
 *  Created on: Sep 29, 2025
 *      Author: cdealba
 */

#include "S25FL064L.h"

extern SPI_HandleTypeDef hspi1;

#define Flash_SSLow()  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, RESET)
#define Flash_SSHigh() 	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, SET)

#define Flash_WPDisable()	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, RESET)
#define Flash_WPEnable()	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, SET)

#define Flash_RSTDisable() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, SET)
#define Flash_RSTEnable() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, SET)


#define Flash_nBlocks 256

void write_enable(){
	uint8_t data=0x06;
	Flash_SSLow();
	HAL_SPI_Transmit(&hflash, &data, 1, Flash_MaxWaitTime);
	Flash_SSHigh();
}


void write_disable(){
	uint8_t data=0x04;
	Flash_SSLow();
	HAL_SPI_Transmit(&hflash, &data, 1, Flash_MaxWaitTime);
	Flash_SSHigh();
}

uint32_t S25FL064_ID(void){
	uint8_t data = 0x9F;
	uint8_t rcv[3];
	Flash_SSLow();
	HAL_SPI_Transmit(&hflash, &data, 1, Flash_MaxWaitTime);
	HAL_SPI_Receive(&hflash, rcv, 3, Flash_MaxWaitTime);
	Flash_SSHigh();
	return((rcv[0]<<16|rcv[1]<<8|rcv[2]));
}

void S25FL064_Read(uint32_t adress,uint32_t size,uint8_t *rcv){
	uint8_t data[4];

	data[0]=0x03;
	data[1] = (adress>>16)&0xFF;
	data[2] = (adress>>8)&0xFF;
	data[3] = (adress)&0xFF;

	Flash_SSLow();
	HAL_SPI_Transmit(&hflash, data, 4, Flash_MaxWaitTime);
	HAL_SPI_Receive(&hflash, rcv, size, Flash_MaxWaitTime);
	Flash_SSHigh();
}

void S25FL064_Write(uint16_t Page,uint8_t *Data){
	uint32_t adress = Page*256;
	uint8_t TxData[260];

	write_enable();

	TxData[0]=0x02;
	TxData[1]= (adress>>16)&0xFF;
	TxData[2]= (adress>>8)&0xFF;
	TxData[3]= (adress)&0xFF;
	for(uint16_t i=0; i != 256;i++){
		TxData[i+4] = Data[i];
	}
	Flash_SSLow();
	HAL_SPI_Transmit(&hflash, &TxData[0], 260, Flash_MaxWaitTime);
	Flash_SSHigh();
}


void S25FL064_Erase(uint16_t sector){
	uint8_t data[4];
	uint32_t adress=sector*16*256;

	write_enable();

	data[0]=0x20;
	data[1]= (adress>>16)&0xFF;
	data[2]= (adress>>8)&0xFF;
	data[3]= (adress)&0xFF;

	Flash_SSLow();
	HAL_SPI_Transmit(&hflash, data, 4, Flash_MaxWaitTime);
	Flash_SSHigh();
}

void S25FL064_chipErase(void){
	uint8_t data=0x60;
	write_enable();
	Flash_SSLow();
	HAL_SPI_Transmit(&hflash, &data, 1, Flash_MaxWaitTime);
	Flash_SSHigh();
	write_disable();
}

void resetFlash(void){
	uint8_t data[2];
	data[0]=0x66;
	data[1]=0x99;
	Flash_SSLow();
	HAL_SPI_Transmit(&hflash, data, 2, Flash_MaxWaitTime);
	Flash_SSHigh();
}

HAL_StatusTypeDef S25FL064_init(void){
	Flash_RSTDisable();
	Flash_WPDisable();
	Flash_SSHigh();
	if(S25FL064_ID()==0) return HAL_ERROR;
	write_enable();
	return HAL_OK;
}

