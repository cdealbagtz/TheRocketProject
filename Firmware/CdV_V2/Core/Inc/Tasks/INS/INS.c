/*
 * INS.c
 *
 *  Created on: 13 jun 2026
 *      Author: Chris
 */


#include "Tasks/INS/INS.h"


void INS_BMP280Task(void){
	static uint32_t BMP280_time = 0;

	if(Config_Configuration.INS_ConfigPackage.INS_Config.BMP280_Time == 0){
		Config_Configuration.INS_ConfigPackage.INS_Config.BMP280_Time = 300;
	}

	if((HAL_GetTick() - BMP280_time) > Config_Configuration.INS_ConfigPackage.INS_Config.BMP280_Time){

		if(BMP280.ID == 0){
			BMP280_init();
		}
		else{
			BMP280_calculate();
		}
		BMP280_time = HAL_GetTick();
	}
}

void INS_MPU6050Task(void){
	static uint32_t MPU6050_time = 0;

	if(Config_Configuration.INS_ConfigPackage.INS_Config.MPU6050_Time == 0){
		Config_Configuration.INS_ConfigPackage.INS_Config.MPU6050_Time = 50;
	}

	if((HAL_GetTick() - MPU6050_time) > Config_Configuration.INS_ConfigPackage.INS_Config.MPU6050_Time){

		if(MPU6050_time == 0){
			MPU6050_Init();
		}
		else{
			MPU6050_Read_All();
		}
		MPU6050_time = HAL_GetTick();
	}
}

void INS_ICM42670Task(void){
	static uint32_t ICM42670_time = 0;

	if(Config_Configuration.INS_ConfigPackage.INS_Config.ICM42670_Time == 0){
		Config_Configuration.INS_ConfigPackage.INS_Config.ICM42670_Time = 50;
	}

	if((HAL_GetTick() - ICM42670_time) > Config_Configuration.INS_ConfigPackage.INS_Config.ICM42670_Time){

		if(ICM42670.ID == 0){
			ICM42670_init();
		}
		else{
			ICM44670_getData();
		}
		ICM42670_time = HAL_GetTick();
	}
}

void INS_Task(void){
	INS_BMP280Task();
	INS_MPU6050Task();
	INS_ICM42670Task();
}
