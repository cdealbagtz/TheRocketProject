/*
 * Memory.c
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#include "Memory.h"

void Memory_Task(void){
	System_Notification_t System_Notification = {
			.NotificationID = TaskID_Memory
	};
	Memory_Write_t		 Memory_WriteRequest;
	Memory_ReadRequest_t Memory_ReadRequest;
	Memory_Read_t		 Memory_ReadAnswer;

	while(osMessageQueueGetCount(Memory_requestQueueHandle)){
		osMessageQueueGet(Memory_requestQueueHandle, &Memory_ReadRequest, 0, 0);
		Memory_ReadAnswer.Adress = Memory_ReadRequest.Adress;
		Memory_ReadAnswer.Size = Memory_ReadRequest.Size;
		S25FL064_Read(Memory_ReadRequest.Adress, Memory_ReadRequest.Size, Memory_ReadAnswer.Data);
		osMessageQueuePut(Memory_readQueueHandle, &Memory_ReadAnswer, 0, 0);
		osDelay(5);
	}
	if(osMessageQueueGetCount(Memory_writeQueueHandle)){
		osMessageQueueGet(Memory_writeQueueHandle, &Memory_WriteRequest, 0, 0);
		if(Memory_WriteRequest.Page == Memory_PerformChipEraseCommand){
			S25FL064_chipErase();
			System_Notification.NotificationInfo = Memory_ChipEraseStarted;
			osMessageQueuePut(System_QueueHandle, &System_Notification, 0, 0);
			osDelay(150000);
			System_Notification.NotificationInfo = Memory_ChipEraseCompleted;
			osMessageQueuePut(System_QueueHandle, &System_Notification, 0, 0);
		}
		else if(Memory_WriteRequest.Page == Memory_PerformConfigEraseCommand){
			S25FL064_Erase(0);
			System_Notification.NotificationInfo = Memory_ConfigEraseStarted;
			osMessageQueuePut(System_QueueHandle, &System_Notification, 0, 0);
			osDelay(320);
			System_Notification.NotificationInfo = Memory_ConfigEraseCompleted;
			osMessageQueuePut(System_QueueHandle, &System_Notification, 0, 0);
		}
		else{
			uint16_t Address = Memory_WriteRequest.Page;
			if(Address < Memory_MaxPage){
				S25FL064_Write(Address, Memory_WriteRequest.Data);
			}
		}
	}
}
