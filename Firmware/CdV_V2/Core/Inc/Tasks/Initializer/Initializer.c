/*
 * Initializer.c
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#include "Initializer.h"


void SafeTask(void){

}

void InitializerTasks(void){
	static uint32_t AuxiliarCounter = 0;
	System_Notification_t Initializer_Notifications = {
			.NotificationID = TaskID_Initializer,
			.NotificationInfo = 0
	};

	switch (MissionState) {
		case STATE_SAFE:

			break;
		case STATE_SELFTEST:

			break;
		default:

			break;
	}
	if(( HAL_GetTick()-AuxiliarCounter)>Initializer_MaxTime){
		Initializer_Notifications.NotificationInfo = Initializer_TimeExceeded;
		osMessageQueuePut(System_QueueHandle, &Initializer_Notifications, 0, 1000);
		AuxiliarCounter = HAL_GetTick();
	}
}
