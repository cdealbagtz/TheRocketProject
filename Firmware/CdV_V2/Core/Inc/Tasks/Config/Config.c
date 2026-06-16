/*
 * Config.c
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#include "Config.h"

Config_ConfigurationPage_t Config_Configuration;

void Config_PyroDefault(void){
	Config_Configuration.Pyro_ConfigPackage.Pyro_Config.Pyro1_Enable = 0;
	Config_Configuration.Pyro_ConfigPackage.Pyro_Config.Pyro2_Enable = 0;
	Config_Configuration.Pyro_ConfigPackage.Pyro_Config.ActivationTime = 3000;
	Config_Configuration.Pyro_ConfigPackage.Pyro_Config.PulseTime = 1000;
}

void Config_SystemDefault(void){
	Config_Configuration.System_ConfigPackage.System_Config.FaultStatus = 0x0F;
}

void Config_ActuatorsDefault(void){
	Config_Configuration.Actuator_ConfigPackage.Actuator_Config.Freq = 50;
	Config_Configuration.Actuator_ConfigPackage.Actuator_Config.Channel[0].Type = 0;
	Config_Configuration.Actuator_ConfigPackage.Actuator_Config.Channel[1].Type = 0;
	Config_Configuration.Actuator_ConfigPackage.Actuator_Config.Channel[2].Type = 0;
	Config_Configuration.Actuator_ConfigPackage.Actuator_Config.Channel[3].Type = 3;
}

void Config_Default(void){
	Config_PyroDefault();
	Config_SystemDefault();
	Config_ActuatorsDefault();
}

void Config_Task(void){
	Memory_Write_t		 Config_WriteRequestData;

	Memory_ReadRequest_t Memory_ReadRequest;
	Memory_Read_t		 Config_ReadRequestData;

	Config_ConfigurationPackage_t ConfigurationPackage;

	if(osMessageQueueGetCount(Config_RequestHandle)){
		uint8_t Request = 0;
		osMessageQueueGet(Config_RequestHandle, &Request, 0, 0);
		switch (Request) {
			case Config_ReadRequest:
				if(osMutexAcquire(MemoryMutexHandle, 5000)==0){
					Memory_ReadRequest.Adress = 0x00;
					Memory_ReadRequest.Size = 256;
					osMessageQueuePut(Memory_requestQueueHandle, &Memory_ReadRequest, 0, 0);
					while(osMessageQueueGetCount(Memory_readQueueHandle)==0){
						osDelay(5);
					}
					osMessageQueueGet(Memory_readQueueHandle, &Config_ReadRequestData, 0, 0);
					osMutexRelease(MemoryMutexHandle);
					for(uint16_t n = 0; n<256;n++){
						ConfigurationPackage.Data[n] = Config_ReadRequestData.Data[n];
					}
					Config_Configuration = ConfigurationPackage.Config_ConfigurationPage;
				}
				break;
			case Config_WriteRequest:
				Config_WriteRequestData. Page = Memory_PerformConfigEraseCommand;
				osMessageQueuePut(Memory_writeQueueHandle, &Config_WriteRequestData, 0, 0);
				ConfigurationPackage.Config_ConfigurationPage = Config_Configuration;
				Config_WriteRequestData.Page = Config_ConfigurationPage;
				for(uint16_t n = 0; n<256;n++){
					Config_WriteRequestData.Data[n] = ConfigurationPackage.Data[n];
				}
				osMessageQueuePut(Memory_writeQueueHandle, &Config_WriteRequestData, 0, 0);

				break;
			case Config_SetDefaultRequest:
				Config_Default();
				break;
			default:
				break;
		}
	}
}
