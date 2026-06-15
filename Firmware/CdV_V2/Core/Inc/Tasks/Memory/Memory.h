/*
 * Memory.h
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#ifndef INC_TASKS_MEMORY_MEMORY_H_
#define INC_TASKS_MEMORY_MEMORY_H_

#include "main.h"
#include "Drivers/Memory_Drivers/S25FL064L.h"
#include "System/System.h"

#define Memory_MaxPage 32768

typedef struct{
	uint16_t Page;
	uint8_t Data[256];
}Memory_Write_t;

typedef struct{
	uint32_t Adress;
	uint8_t Size;
	uint8_t Data[256];
}Memory_Read_t;

typedef struct{
	uint32_t Adress;
	uint8_t Size;
}Memory_ReadRequest_t;

typedef enum{
	Memory_PerformChipEraseCommand		= 0xFFF0,
	Memory_PerformConfigEraseCommand	= 0xFFF1,
	Memory_InitCommand					= 0xFFF2
}Memory_WirteExtraCommands_e;

extern osMessageQueueId_t Memory_requestQueueHandle;
extern osMessageQueueId_t Memory_readQueueHandle;
extern osMessageQueueId_t Memory_writeQueueHandle;

void Memory_Task(void);

#endif /* INC_TASKS_MEMORY_MEMORY_H_ */
