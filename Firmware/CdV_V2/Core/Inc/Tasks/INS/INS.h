/*
 * INS.h
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */

#ifndef INC_TASKS_INS_INS_H_
#define INC_TASKS_INS_INS_H_

#include "main.h"
#include "System/System.h"
#include "Tasks/Config/Config.h"

#include "Drivers/INS_Drivers/BMP280/BMP280.h"
#include "Drivers/INS_Drivers/IMU/ICM42670.h"
#include "Drivers/INS_Drivers/IMU/MPU6050.h"


#define BMP280_TIME 250

void INS_Task(void);

#endif /* INC_TASKS_INS_INS_H_ */
