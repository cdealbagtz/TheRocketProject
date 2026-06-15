/*
 * Actuators.c
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#include "Actuators.h"

Actuator_ConfigPackage_t TestActuatorConfig;

void Actuators_setSafeValues(Actuator_Config_t *ConfigData){
	htim2.Instance->CCR1 = (uint16_t)ConfigData->Channel[0].InitialValue+500;
	htim2.Instance->CCR2 = (uint16_t)ConfigData->Channel[1].InitialValue+500;
	htim2.Instance->CCR3 = (uint16_t)ConfigData->Channel[2].InitialValue+500;
	htim2.Instance->CCR4 = (uint16_t)ConfigData->Channel[3].InitialValue+500;
}

HAL_StatusTypeDef Actuators_InitChannels(Actuator_Config_t *ConfigData){
	HAL_StatusTypeDef Result = 0;

	Actuators_setSafeValues(ConfigData);

	if(ConfigData->Channel[0].Type != Actuators_OFF){
		Result |= HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	}
	if(ConfigData->Channel[1].Type != Actuators_OFF){
		Result |= HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	}
	if(ConfigData->Channel[2].Type != Actuators_OFF){
		Result |= HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	}
	if(ConfigData->Channel[3].Type != Actuators_OFF){
		Result |= HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	}
	return Result;
}

void Actuators_ChangeChannelValue(Actuator_Config_t *ConfigData,Actuators_Channels Channel, uint16_t Value){

	if(ConfigData->Channel[Channel].Type == Actuators_Servo){
		if(Value>2500){
			Value = 2500;
		}
		else if(Value < 500){
			Value = 500;
		}
	}
	else if(ConfigData->Channel[Channel].Type == Actuators_Recovery){
		if(Value >= 1){
			Value = ConfigData->Channel[Channel].FinalValue;
		}
		else{
			Value = ConfigData->Channel[Channel].InitialValue;
		}
	}
	else if(ConfigData->Channel[Channel].Type == Actuators_Buzzer){
		if(Value >= 1){
			Value = 0;
		}
		else{
			Value = htim2.Init.Period+1;
		}
	}
	else{
		Value = 0;
	}

	switch (Channel) {
		case Actuators_Channel1:
			htim2.Instance->CCR1 = Value;
			break;
		case Actuators_Channel2:
			htim2.Instance->CCR2 = Value;
			break;
		case Actuators_Channel3:
			htim2.Instance->CCR3 = Value;
			break;
		case Actuators_Channel4:
			htim2.Instance->CCR4 = Value;
			break;
		default:
			break;
	}
}

HAL_StatusTypeDef Actuators_SetFrequency(uint16_t Freq){
	HAL_StatusTypeDef Result;
	if(Freq <= 0) Freq = 50;
	HAL_TIM_PWM_DeInit(&htim2);
	htim2.Init.Prescaler = System_Timer2Freq/(Freq*(htim2.Init.Period+1))-1;
	Result = HAL_TIM_PWM_Init(&htim2);
	return Result;
}

HAL_StatusTypeDef Actuators_Init(Actuator_Config_t *ConfigData){
	HAL_StatusTypeDef Result;
	Result = Actuators_SetFrequency(ConfigData->Freq);
	if(Result == HAL_OK){
		Result = Actuators_InitChannels(ConfigData);
	}

	return Result;
}

HAL_StatusTypeDef Actuators_ChangeConfig(Actuator_Config_t *ConfigData){
	HAL_StatusTypeDef Result = HAL_OK;

	if(ConfigData->Channel[0].Type == Actuators_OFF){
		Result |= HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	}
	if(ConfigData->Channel[1].Type == Actuators_OFF){
		Result |= HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
	}
	if(ConfigData->Channel[2].Type == Actuators_OFF){
		Result |= HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
	}
	if(ConfigData->Channel[3].Type == Actuators_OFF){
		Result |= HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
	}

	Result |= Actuators_InitChannels(ConfigData);

	return Result;
}

void Actuators_buzzerNotifications(System_BuzzerNotifications_e ConfigState, Actuator_Config_t *ConfigData){
	static uint32_t previosTime = 0;
	static System_BuzzerNotifications_e ActualState = System_buzzerOff;
	static uint8_t buzzerValue = 0;

	if(ConfigState != System_buzzerNoChange){
		ActualState = ConfigState;
		previosTime = HAL_GetTick();
		buzzerValue = 0;
	}

	switch (ActualState) {
		case System_buzzerOff:
			buzzerValue = 0;
			break;

		case System_buzzerInitCompleted:
			static uint8_t initCount = 0;
			if(initCount<3){
				if( (HAL_GetTick()-previosTime)> 500){
					if(buzzerValue == 0){
						buzzerValue = 1;
						initCount++;
					}
					else if(buzzerValue == 1){
						buzzerValue = 0;
					}
					previosTime = HAL_GetTick();
				}
			}
			else{
				if( (HAL_GetTick()-previosTime)> 1000){
					buzzerValue = 0;
					initCount = 0;
					previosTime = HAL_GetTick();
					ActualState = System_buzzerOff;
				}
			}
			break;

		case System_buzzerPyroStarted:
			if( (HAL_GetTick()-previosTime)> 500){
				previosTime = HAL_GetTick();
				if(buzzerValue){
					buzzerValue = 0;
				}
				else{
					buzzerValue = 1;
				}
			}
			break;
		case System_buzzerFAULT:
			buzzerValue = 1;
			break;
		case System_buzzerLanded:
			if(buzzerValue){
				if( (HAL_GetTick()-previosTime)> 500){
					previosTime = HAL_GetTick();
					buzzerValue = 0;
				}
			}
			else{
				if( (HAL_GetTick()-previosTime)> 5000){
					previosTime = HAL_GetTick();
					buzzerValue = 1;
				}

			}
			break;
		default:
			buzzerValue = 1;
			break;
	}


		for(uint8_t n = 0;n<4;n++){
			if(ConfigData->Channel[n].Type == Actuators_Buzzer){
				Actuators_ChangeChannelValue(ConfigData,n,buzzerValue);
			}
		}

}


void Actuators_Task(void){
	Actuator_Request_t Actuator_Request;
	static System_Notification_t System_Notification;
	System_BuzzerNotifications_e BuzzerConfig = System_buzzerNoChange;

	while(osMessageQueueGetCount(Actuator_QueueHandle)>0){
		osMessageQueueGet(Actuator_QueueHandle, &Actuator_Request, 0, 0);
		switch (Actuator_Request.RequestID) {
			case Actuators_SetValueID:
				Actuators_ChangeChannelValue(&TestActuatorConfig.Actuator_Config, Actuator_Request.Channel, Actuator_Request.Data);
				break;
			case Actuators_BufferSetID:
				BuzzerConfig = Actuator_Request.Data;
				break;
			case Actuators_SetFreqID:
				if(Actuators_SetFrequency(Actuator_Request.Data) != HAL_OK){
					System_Notification.NotificationID = TaskID_Actuators;
					System_Notification.NotificationInfo = Actuators_InitFailed;
					osMessageQueuePut(System_QueueHandle, &System_Notification, 0, 0);
				}
				break;
			case Actuators_SafeValuesID:
				Actuators_setSafeValues(&TestActuatorConfig.Actuator_Config);
				break;
			case Actuators_ChangeConfigID:


				if(Actuators_ChangeConfig(&TestActuatorConfig.Actuator_Config) != HAL_OK){
					System_Notification.NotificationID = TaskID_Actuators;
					System_Notification.NotificationInfo = Actuators_InitFailed;
					osMessageQueuePut(System_QueueHandle, &System_Notification, 0, 0);
				}
				break;
			case Actuators_InitID:
				if(Actuators_Init(&TestActuatorConfig.Actuator_Config) != HAL_OK){
					System_Notification.NotificationID = TaskID_Actuators;
					System_Notification.NotificationInfo = Actuators_InitFailed;
				}
				else{
					System_Notification.NotificationID = TaskID_Actuators;
					System_Notification.NotificationInfo = Actuators_InitComplete;
				}
				osMessageQueuePut(System_QueueHandle, &System_Notification, 0, 0);
				break;
			default:
				break;
		}
	}
	Actuators_buzzerNotifications(BuzzerConfig, &TestActuatorConfig.Actuator_Config);
}




