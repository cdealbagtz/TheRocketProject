/*
 * System.c
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */


#include "System.h"


/*Global system variables*/
System_MissionState_e MissionState = STATE_SAFE;

void System_SetSystemLed(System_LedStatus_e ActualState){
	static uint32_t previosTime;

	switch (ActualState) {
		case System_ledOK:
			if( (HAL_GetTick()-previosTime)> System_ledHeartbeat){
				previosTime = HAL_GetTick();
				HAL_GPIO_TogglePin(System_LED_GPIO_Port, System_LED_Pin);
			}
			break;
		case System_ledPyroStarted:
			if( (HAL_GetTick()-previosTime)> System_ledWarning){
				previosTime = HAL_GetTick();
				HAL_GPIO_TogglePin(System_LED_GPIO_Port, System_LED_Pin);
			}
			break;
		case System_ledFAULT:
			HAL_GPIO_WritePin(System_LED_GPIO_Port, System_LED_Pin, SET);
			break;
		default:
			HAL_GPIO_WritePin(System_LED_GPIO_Port, System_LED_Pin, SET);
			break;
	}
}

void System_StartParachuteDeployment(void){
	Actuator_Request_t Actuator_Request = {
			.RequestID = Actuators_BufferSetID,
			.Data = System_buzzerPyroStarted
	};
	osMessageQueuePut(Actuator_QueueHandle, &Actuator_Request, 6, 0);
	osTimerStart(DeployParachuteTimerHandle, System_PyroDetonationtime);

}
