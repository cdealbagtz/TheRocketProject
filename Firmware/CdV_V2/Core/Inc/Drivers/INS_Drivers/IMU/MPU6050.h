/*
*************************
*                       *
* İbrahim Cahit Özdemir *
*                       *
*     October 2021      *
*                       *
*************************
*/

#ifndef INC_GY521_H_
#define INC_GY521_H_

#endif /* INC_GY521_H_ */

#include "main.h"
#include "i2c.h"
#include "math.h"

#include "Tasks/Config/Config.h"


#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_CONFIG_REG 0x1B
#define GYRO_XOUT_H_REG 0x43

// MPU6050 structure
typedef struct {

    int16_t Accel_X_RAW;
    int16_t Accel_Y_RAW;
    int16_t Accel_Z_RAW;

    int16_t Gyro_X_RAW;
    int16_t Gyro_Y_RAW;
    int16_t Gyro_Z_RAW;


    int16_t Temperature;

	float ax_g;
	float ay_g;
	float az_g;

	float gx_dps;
	float gy_dps;
	float gz_dps;

} MPU6050_t;

extern MPU6050_t MPU6050;

uint8_t MPU6050_Init(void);

void MPU6050_Read_All(void);

