/*
 * Actuators.h
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#ifndef INC_TASKS_ACTUATORS_ACTUATORS_H_
#define INC_TASKS_ACTUATORS_ACTUATORS_H_

#include "main.h"
#include "tim.h"
#include "System/System.h"
#include "Tasks/Config/Config.h"

#define System_Timer2Freq  108*1000000

extern TIM_HandleTypeDef htim2;

typedef enum{
	Actuators_Channel1,
	Actuators_Channel2,
	Actuators_Channel3,
	Actuators_Channel4
}Actuators_Channels;

typedef enum{
	Actuators_OFF,
	Actuators_Servo,
	Actuators_Recovery,
	Actuators_Buzzer
}Actuators_Type;

typedef enum{
	Actuators_SetValueID,
	Actuators_BufferSetID,
	Actuators_SetFreqID,
	Actuators_SafeValuesID,
	Actuators_ChangeConfigID,
	Actuators_InitID
}Actuators_RequestID;

typedef struct{
	uint8_t  RequestID;
	uint8_t  Channel;
	uint16_t Data;
}Actuator_Request_t;

extern osMessageQueueId_t Actuator_QueueHandle;

void Actuators_Task(void);

#endif /* INC_TASKS_ACTUATORS_ACTUATORS_H_ */
