/*
 * MissionManagerTask.c
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#include "MissionManager.h"

void MissionManager_ActuatorsNotifications(void){

}

void MissionManager_InitializerNotifications(Initializer_Notifications_e Initializer_Notifications){
	switch (Initializer_Notifications) {
		case Initializer_SafeDone:
			MissionState = STATE_SELFTEST;
			break;
		case Initializer_SelfTestDone:
			MissionState = STATE_STANDBY;
			break;
		case Initializer_TimeExceeded:
			MissionState = STATE_FAULT;
			break;
		case Initializer_FaultRegister:
			MissionState = STATE_FAULT;
			break;
		default:
			MissionState = STATE_FAULT;
			break;
	}
}

uint8_t ConfigRequestTest = 0;

Actuator_Request_t Actuator_RequestTest = {
	.RequestID = TaskID_Actuators
};
uint8_t PutMessageTest = 0;

void MissionManager_Task(void){
	System_Notification_t System_Notification;
	static System_LedStatus_e System_LedStatus = System_ledOK;

	while(osMessageQueueGetCount(System_QueueHandle)>0){
		osMessageQueueGet(System_QueueHandle, &System_Notification, 0, 0);

		switch (System_Notification.NotificationID) {
			case TaskID_Actuators:

				break;
			case TaskID_Memory:

				break;
			case TaskID_Initializer:
				MissionManager_InitializerNotifications(System_Notification.NotificationInfo);

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
	System_SetSystemLed(System_LedStatus);
}

