/*
 * Initializer.h
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#ifndef INC_TASKS_INITIALIZER_INITIALIZER_H_
#define INC_TASKS_INITIALIZER_INITIALIZER_H_

#include "main.h"
#include "System/System.h"
#include "Tasks/Actuators/Actuators.h"
#include "Tasks/Config/Config.h"

/*  Max init time in ms
 */

#define Initializer_MaxTime 15000

void Initializer_Task(void);

#endif /* INC_TASKS_INITIALIZER_INITIALIZER_H_ */
