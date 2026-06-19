/*
 * Initializer.c
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#include "Initializer.h"






void Initializer_Task(void){
	static uint32_t AuxiliarCounter = 0;
	System_Notification_t Initializer_Notifications = {
			.NotificationID = TaskID_Initializer,
			.NotificationInfo = 0
	};
	uint8_t ConfigRequest = Config_ReadRequest;

	switch (MissionState) {
		case STATE_SAFE:
			static uint8_t Initcounter = 0;
			while(Config_Configuration.System_ConfigPackage.System_Config.FaultStatus == 0x00){
				if(Initcounter>10){
					Initializer_Notifications.NotificationInfo = Initializer_TimeExceeded;
					osMessageQueuePut(System_QueueHandle, &Initializer_Notifications, 0, 1000);
					Initcounter = 0;
					return;
				}

				osMessageQueuePut(Config_RequestHandle, &ConfigRequest, 0, 0);
				Initcounter++;
				osDelay(50);
			}
			switch (Config_Configuration.System_ConfigPackage.System_Config.FaultStatus) {
				case 0xFF:
					uint8_t ConfigRequest = Config_SetDefaultRequest;
					osMessageQueuePut(Config_RequestHandle, &ConfigRequest, 0, 0);
					osDelay(300);
					break;
				case 0x0F:
					Actuator_Request_t Actuator_Request = {
							.RequestID = Actuators_InitID
					};
					osMessageQueuePut(Actuator_QueueHandle, &Actuator_Request, 0, 0);
					osDelay(100);
					Initializer_Notifications.NotificationInfo = Initializer_SafeDone;
					osMessageQueuePut(System_QueueHandle, &Initializer_Notifications, 0, 1000);
					break;
				case 0xAA:
					Initializer_Notifications.NotificationInfo = Initializer_FaultRegister;
					osMessageQueuePut(System_QueueHandle, &Initializer_Notifications, 0, 1000);
					break;
				default:
					break;
			}
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
