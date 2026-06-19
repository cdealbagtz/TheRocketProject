/*
*************************
*                       *
* İbrahim Cahit Özdemir *
*                       *
*     October 2021      *
*                       *
*************************
*/

#include "Drivers/INS_Drivers/IMU/MPU6050.h"



// Setup MPU6050
#define MPU6050_ADDR 0xD0
const uint16_t i2c_timeout = 100;
const double Accel_Z_corrector = 14418.0;

MPU6050_t MPU6050;

uint8_t MPU6050_Init(void) {
    uint8_t check;
    uint8_t Data;

    // check device ID WHO_AM_I

    HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, i2c_timeout);

    if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
    {
        // power management register 0X6B we should write all 0's to wake the sensor up
        Data = 0;
        HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, i2c_timeout);

        // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
        Data = 0x07;
        HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, i2c_timeout);

        // Set accelerometer configuration in ACCEL_CONFIG Register
        // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
        Data = 0x00;
        HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, i2c_timeout);

        // Set Gyroscopic configuration in GYRO_CONFIG Register
        // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
        Data = 0x00;
        HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, i2c_timeout);
        return 0;
    }
    return 1;
}


void MPU6050_Read_All(void) {
    uint8_t Rec_Data[14];

    // Read 14 BYTES of data starting from ACCEL_XOUT_H register

    HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 14, i2c_timeout);

    MPU6050.Accel_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]) - Config_Configuration.INS_ConfigPackage.INS_Config.MPU6050_Bias.ACC[0];
    MPU6050.Accel_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]) - Config_Configuration.INS_ConfigPackage.INS_Config.MPU6050_Bias.ACC[1];
    MPU6050.Accel_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]) - Config_Configuration.INS_ConfigPackage.INS_Config.MPU6050_Bias.ACC[2];
    MPU6050.Temperature = (int16_t) (Rec_Data[6] << 8 | Rec_Data[7]);
    MPU6050.Gyro_X_RAW = (int16_t) (Rec_Data[8] << 8 | Rec_Data[9])   - Config_Configuration.INS_ConfigPackage.INS_Config.MPU6050_Bias.Gy[0];
    MPU6050.Gyro_Y_RAW = (int16_t) (Rec_Data[10] << 8 | Rec_Data[11]) - Config_Configuration.INS_ConfigPackage.INS_Config.MPU6050_Bias.Gy[1];
    MPU6050.Gyro_Z_RAW = (int16_t) (Rec_Data[12] << 8 | Rec_Data[13]) - Config_Configuration.INS_ConfigPackage.INS_Config.MPU6050_Bias.Gy[2];

    MPU6050.ax_g = MPU6050.Accel_X_RAW / 16384.0;
    MPU6050.ay_g = MPU6050.Accel_Y_RAW / 16384.0;
    MPU6050.az_g = MPU6050.Accel_Z_RAW / Accel_Z_corrector;

    MPU6050.gx_dps = MPU6050.Gyro_X_RAW / 131.0;
    MPU6050.gy_dps = MPU6050.Gyro_Y_RAW / 131.0;
    MPU6050.gz_dps = MPU6050.Gyro_Z_RAW / 131.0;



}


