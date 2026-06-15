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


typedef struct{

}Config_Request_t;

typedef enum{
	Config_ConfigurationPage = 0x00,
	Config_GainsPage		 = 0x01
}Config_MemoryMap_e;

typedef struct{
	uint8_t FaultStatus;
	uint8_t Reserved[7];
}System_Config_t;

typedef union{
	System_Config_t System_Config;
	uint8_t Package[8];
}System_ConfigPackage_t;

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

typedef struct{
	System_ConfigPackage_t   System_ConfigPackage;
	Actuator_ConfigPackage_t Actuator_ConfigPackage;
	uint8_t Reserved[232];
}Config_Configuration_t;

extern Config_Configuration_t Config_Configuration;

void Config_Task(void);

#endif /* INC_TASKS_CONFIG_CONFIG_H_ */
