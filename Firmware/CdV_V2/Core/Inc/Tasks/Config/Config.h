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
	uint8_t  Type:2;
	uint16_t InitialValue:11;
	uint16_t FinalValue:11;
}Actuator_ChannelConfig;

typedef struct{
	Actuator_ChannelConfig Channel[4];
	uint16_t Freq;
}Actuator_Config_t;

typedef union{
	Actuator_Config_t Actuator_Config;
	uint8_t Package[14];
}Actuator_ConfigPackage_t;

#endif /* INC_TASKS_CONFIG_CONFIG_H_ */
