/*
 * MissionManagerTask.c
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#include "MissionManager.h"

void MissionManager_ActuatorsNotifications(void){

}

void MissionManager_InitializerNotifications(void){

}

uint8_t ConfigRequestTest = 0;

Actuator_Request_t Actuator_RequestTest = {
	.RequestID = TaskID_Actuators
};
uint8_t PutMessageTest = 0;

void MissionManager_Task(void){
	System_Notification_t System_Notification;

	while(osMessageQueueGetCount(System_QueueHandle)>0){
		osMessageQueueGet(System_QueueHandle, &System_Notification, 0, 0);

		switch (System_Notification.NotificationID) {
			case TaskID_Actuators:

				break;
			case TaskID_Memory:

				break;
			case TaskID_Initializer:

				break;
			case TaskID_CommandInterface:

				break;
			case TaskID_Config:

				break;
			case TaskID_INS:

				break;
			case TaskID_Blackbox:

				break;
			case TaskID_Fault:

				break;
			default:
				break;

			}
	}

	if(PutMessageTest == 1){

		osMessageQueuePut(Actuator_QueueHandle, &Actuator_RequestTest, 0, 0);
		PutMessageTest = 0;
	}
	else if(PutMessageTest == 2){
		osMessageQueuePut(Config_RequestHandle, &ConfigRequestTest, 0, 0);
		PutMessageTest = 0;
	}
	System_SetSystemLed(0);
}

