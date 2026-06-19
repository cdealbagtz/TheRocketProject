/*
 * Config.h
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#ifndef INC_TASKS_CONFIG_CONFIG_H_
#define INC_TASKS_CONFIG_CONFIG_H_

#include "main.h"

#include "System/System.h"
#include "Tasks/Memory/Memory.h"


typedef enum{
	Config_ConfigurationPage = 0x00,
	Config_GainsPage		 = 0x01
}Config_MemoryMap_e;

typedef enum{
	Config_ReadRequest,
	Config_WriteRequest,
	Config_SetDefaultRequest
}Config_Request_e;

/********************************SYSTEM*******************************/

typedef struct{
	uint8_t FaultStatus;
	uint8_t Reserved[7];
}System_Config_t;

typedef union{
	System_Config_t System_Config;
	uint8_t Package[8];
}System_ConfigPackage_t;

/*********************************Pyro*******************************/

typedef struct{
	uint8_t Pyro1_Enable:1;
	uint8_t Pyro2_Enable:1;
	uint16_t ActivationTime:15;
	uint16_t PulseTime:15;
}Pyro_Config_t;

typedef union{
	Pyro_Config_t Pyro_Config;
	uint8_t Data[4];
}Pyro_ConfigPackage_t;

/********************************Actuator*******************************/

typedef struct{
	uint8_t  Type:2;
	uint16_t InitialValue:11;
	uint16_t FinalValue:11;
}Actuator_ChannelConfig_t;

typedef struct{
	Actuator_ChannelConfig_t Channel[4];
	uint16_t Freq;
	uint8_t Reserved[2];
}Actuator_Config_t;

typedef union{
	Actuator_Config_t Actuator_Config;
	uint8_t Package[16];
}Actuator_ConfigPackage_t;

/********************************INS*******************************/

typedef struct{
	uint16_t ACC[3];
	uint16_t Gy [3];
}IMU_BiasData_t;

typedef struct{
	IMU_BiasData_t MPU6050_Bias;
	IMU_BiasData_t ICM42670_Bias;
	uint16_t BMP280_Time;
	uint16_t MPU6050_Time;
	uint16_t ICM42670_Time;
	uint8_t Reserved[34];
}INS_Config_t;

typedef union{
	INS_Config_t INS_Config;
	uint8_t Package[64];
}INS_ConfigPackage_t;

typedef struct{
	System_ConfigPackage_t   System_ConfigPackage;
	Actuator_ConfigPackage_t Actuator_ConfigPackage;
	Pyro_ConfigPackage_t Pyro_ConfigPackage;
	INS_ConfigPackage_t INS_ConfigPackage;
	uint8_t Reserved[164];
}Config_ConfigurationPage_t;

typedef union{
	Config_ConfigurationPage_t Config_ConfigurationPage;
	uint8_t Data[255];
}Config_ConfigurationPackage_t;

extern Config_ConfigurationPage_t Config_Configuration;
extern osMessageQueueId_t Config_RequestHandle;

void Config_Task(void);

#endif /* INC_TASKS_CONFIG_CONFIG_H_ */
