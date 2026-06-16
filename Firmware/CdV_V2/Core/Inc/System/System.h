/*
 * System.h
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#ifndef INC_SYSTEM_SYSTEM_H_
#define INC_SYSTEM_SYSTEM_H_

#include "main.h"
#include "gpio.h"
#include "cmsis_os2.h"

#include "Tasks/Actuators/Actuators.h"

#define System_ledHeartbeat 1000
#define System_ledWarning   100

#define System_PyroDetonationtime 	5000
#define System_PyroPulsetime		5000

typedef enum{
	System_ledOK,
	System_ledPyroStarted,
	System_ledFAULT
}System_LedStatus_e;

typedef enum{
	System_buzzerNoChange,
	System_buzzerOff,
	System_buzzerInitCompleted,
	System_buzzerPyroStarted,
	System_buzzerFAULT,
	System_buzzerLanded
}System_BuzzerNotifications_e;

typedef enum{
	STATE_SAFE,
	STATE_SELFTEST,
	STATE_STANDBY,
	STATE_ARMED,
	STATE_BOOST,
	STATE_COAST,
	STATE_APOGEE_DETECTED,
	STATE_RECOVERY_DEPLOYED,
	STATE_DESCENT,
	STATE_LANDED,
	STATE_FAULT
}System_MissionState_e;

typedef enum{
	TaskID_MissionManager,
	TaskID_Actuators,
	TaskID_Memory,
	TaskID_Initializer,
	TaskID_CommandInterface,
	TaskID_Config,
	TaskID_INS,
	TaskID_Blackbox,
	TaskID_Fault
}System_TaskID;

typedef enum{
	Initializer_SafeDone,
	Initializer_SelfTestDone,
	Initializer_FaultRegister,
	Initializer_TimeExceeded
}Initializer_Notifications_e;

typedef enum{
	Actuators_InitComplete,
	Actuators_InitFailed,
	Actuators_Fault
}Actuators_Notifications_e;

typedef enum{
	Memory_InitComplete,
	Memory_InitFailed,
	Memory_ChipEraseStarted,
	Memory_ChipEraseCompleted,
	Memory_ConfigEraseStarted,
	Memory_ConfigEraseCompleted
}Memory_Notifications_e;

typedef struct{
	System_TaskID 	NotificationID;
	uint8_t 		NotificationInfo;
}System_Notification_t;



/*Global system variables*/
extern System_MissionState_e MissionState;

/*Queues ID*/
extern osMessageQueueId_t System_QueueHandle;

extern osTimerId_t DeployParachuteTimerHandle;
extern osTimerId_t ParachuteDeploymentPulseHandle;

/*System functions*/
void System_SetSystemLed(System_LedStatus_e ActualState);

#endif /* INC_SYSTEM_SYSTEM_H_ */
