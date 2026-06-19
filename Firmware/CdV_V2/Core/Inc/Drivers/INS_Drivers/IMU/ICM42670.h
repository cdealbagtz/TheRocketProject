 /*
 * ICM42670.h
 *
 * Created on: Jul 28, 2025
 * Author: Nathan Netzel
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Nathan Netzel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the conditions of the MIT License.
 */

#ifndef INC_ICM42670_H_
#define INC_ICM42670_H_


#include "main.h"
#include <spi.h>

#include "Tasks/Config/Config.h"

// --- Registers ---
#define ICM_MCLK_RDY		0x00
#define ICM_INT_CONFIG      0x06
#define ICM_PWR_MGMT0		0x1F
#define ICM_GYRO_CONFIG0	0x20
#define ICM_ACCEL_CONFIG0	0x21
#define ICM_TEMP_CONFIG0	0x22
#define ICM_GYRO_CONFIG1	0x23
#define ICM_ACCEL_CONFIG1	0x24
#define ICM_INT_SOURCE0		0x2B
#define ICM_INT_SOURCE1		0x2C
#define ICM_INT_SOURCE3		0x2D
#define ICM_INT_SOURCE4		0x2E
#define ICM_WHO_AM_I		0x75

// --- Output Data Addresses ---
#define ICM_T_DATA_ADDRESS_INIT 0x09
#define ICM_OUT_TEMP_H		0x09
#define ICM_OUT_TEMP_L		0x0A

#define ICM_A_DATA_ADDRESS_INIT 0x0B
#define ICM_OUTX_H_A		0x0B
#define ICM_OUTX_L_A		0x0C
#define ICM_OUTY_H_A		0x0D
#define ICM_OUTY_L_A		0x0E
#define ICM_OUTZ_H_A		0x0F
#define ICM_OUTZ_L_A		0x10

#define ICM_G_DATA_ADDRESS_INIT 0x11
#define ICM_OUTX_H_G		0x11
#define ICM_OUTX_L_G		0x12
#define ICM_OUTY_H_G		0x13
#define ICM_OUTY_L_G		0x14
#define ICM_OUTZ_H_G		0x15
#define ICM_OUTZ_L_G		0x16

// --- Device ID ---
#define ICM_DEVICE_ID		0x67	/**< Expected ID value for WHO_AM_I */

// --- Accelerometer Output Data Rates ---
#define ICM_A_ODR_1600		0x05
#define ICM_A_ODR_0800		0x06
#define ICM_A_ODR_0400		0x07
#define ICM_A_ODR_0200		0x08
#define ICM_A_ODR_0100		0x09
#define ICM_A_ODR_0050		0x0A
#define ICM_A_ODR_0025		0x0B
#define ICM_A_ODR_12_5		0x0C
#define ICM_A_ODR_6_25		0x0D
#define ICM_A_ODR_3_125		0x0E
#define ICM_A_ODR_1_5625	0x0F

// --- Gyrometer Output Data Rates ---
#define ICM_G_ODR_1600		0x05
#define ICM_G_ODR_0800		0x06
#define ICM_G_ODR_0400		0x07
#define ICM_G_ODR_0200		0x08
#define ICM_G_ODR_0100		0x09
#define ICM_G_ODR_0050		0x0A
#define ICM_G_ODR_0025		0x0B
#define ICM_G_ODR_12_5		0x0C

// --- Accelerometer Modes ---
#define ICM_A_LOW_POWER_MODE	0x02
#define ICM_A_LOW_NOISE_MODE	0x03

// --- Gyrometer Modes ---
#define ICM_G_STANDBY_MODE		0x04
#define ICM_G_LOW_NOISE_MODE	0x0C

// --- Accelerometer Ranges ---
#define ICM_A_RANGE_16		0x00
#define ICM_A_RANGE_08		0x20
#define ICM_A_RANGE_04		0x40
#define ICM_A_RANGE_02		0x60

// --- Gyroscope Ranges ---
#define ICM_G_RANGE_2000	0x00
#define ICM_G_RANGE_1000	0x20
#define ICM_G_RANGE_0500	0x40
#define ICM_G_RANGE_0250	0x60

// --- Interrupt Configuration ---
#define ICM_INT1_ACTIVEHIGH		0x01
#define ICM_INT2_ACTIVEHIGH		0x08
#define ICM_INT2_ACTIVELOW  	0x00
#define ICM_INT1_PULSEMODE		0x00
#define ICM_INT1_LATCHMODE 		0x04
#define ICM_INT2_PULSEMODE		0x00
#define ICM_INT2_LATCHMODE 		0x20

#define ICM_INT_DATA_READY		0x08

// --- SPI Command Prefixes ---
#define ICM_Read_Command		0x80
#define ICM_Write_command		0x00

#define ICM_Timeout	10 /**< Default timeout (ms) */


// --- Error Status Enumeration ---
/**
 * @brief Status return values for ICM42670 operations
 */
typedef enum {
    ICM_NO_ERROR           = 0x00U,  /**< No error */
    ICM_ERROR              = 0x01U,  /**< Generic error */
    ICM_HAL_ERROR          = 0x02U,  /**< HAL communication failure */
    ICM_INV_REG_DATA_READ  = 0x03U,  /**< Register readback mismatch */
    ICM_ID_VERIFY_ERROR    = 0x04U   /**< ID mismatch */
} ICM42670_Error_TypeDef;


// --- Hardware Interface Structure ---
/**
 * @brief Structure for SPI communication with ICM42670
 */
typedef struct {
    SPI_HandleTypeDef *SPIhandler;  /**< SPI handler */
    GPIO_TypeDef *CS_GPIOport;      /**< Chip Select GPIO port */
    uint16_t CS_GPIOpin;            /**< Chip Select GPIO pin */
    uint8_t SPI_Timeout;            /**< SPI timeout in milliseconds */
} ICM42670_HW_InitTypeDef;


// --- Sensor Data Structures ---
/**
 * @brief Structure for 3-axis sensor data (accelerometer or gyroscope)
 */
typedef union {
    struct {
        int16_t DX;
        int16_t DY;
        int16_t DZ;
    } axes;
    uint8_t raw_data[6];
}ICM42670_Data_TypeDef;

/**
 * @brief Structure for temperature data
 */
typedef union {
    struct {
        int16_t T;
    } temp;
    uint8_t raw_data[2];
}ICM42670_Temp_Data_TypeDef;


// --- Function Prototypes ---

/**
 * @brief Configure the gyroscope output data rate and range.
 * @param ICM42670_Handler Pointer to initialized ICM42670 hardware interface structure.
 * @param ICM42670_G_Rate Output data rate (ODR) setting.
 * @param ICM42670_G_Range Full-scale gyroscope range setting.
 * @retval ICM42670_Error_TypeDef Status of the configuration operation.
 */
ICM42670_Error_TypeDef ICM42670_Set_Gyrometer(ICM42670_HW_InitTypeDef *, uint8_t, uint8_t, uint8_t);

/**
 * @brief Configure the accelerometer output data rate and range.
 * @param ICM42670_Handler Pointer to initialized ICM42670 hardware interface structure.
 * @param ICM42670_A_Rate Output data rate (ODR) setting.
 * @param ICM42670_A_Range Full-scale accelerometer range setting.
 * @retval ICM42670_Error_TypeDef Status of the configuration operation.
 */
ICM42670_Error_TypeDef ICM42670_Set_Accelerometer(ICM42670_HW_InitTypeDef *, uint8_t, uint8_t, uint8_t);


/**
 * @brief Configure interrupts for data-ready signals on INT1.
 * @param ICM42670_Handler Pointer to initialized ICM42670 hardware interface structure.
 * @retval ICM42670_Error_TypeDef Status of the configuration operation.
 */
ICM42670_Error_TypeDef ICM42670_Set_Interrupt_Measurement(ICM42670_HW_InitTypeDef *);

/**
 * @brief Verify the device ID by reading the WHO_AM_I register.
 * @param ICM42670_Handler Pointer to initialized ICM42670 hardware interface structure.
 * @retval ICM42670_Error_TypeDef ICM_NO_ERROR if ID matches, otherwise ICM_ID_VERIFY_ERROR.
 */
ICM42670_Error_TypeDef ICM42670_ID_Verify(ICM42670_HW_InitTypeDef *);

/**
 * @brief Read accelerometer X, Y, Z axis data.
 * @param ICM42670_Handler Pointer to initialized ICM42670 hardware interface structure.
 * @param ICM42670_Data Pointer to structure to receive accelerometer data.
 * @retval ICM42670_Error_TypeDef Status of the read operation.
 */
ICM42670_Error_TypeDef ICM42670_A_Data_Read(ICM42670_HW_InitTypeDef *, ICM42670_Data_TypeDef *);

/**
 * @brief Read gyroscope X, Y, Z axis data.
 * @param ICM42670_Handler Pointer to initialized ICM42670 hardware interface structure.
 * @param ICM42670_Data Pointer to structure to receive gyroscope data.
 * @retval ICM42670_Error_TypeDef Status of the read operation.
 */
ICM42670_Error_TypeDef ICM42670_G_Data_Read(ICM42670_HW_InitTypeDef *, ICM42670_Data_TypeDef *);

/**
 * @brief Read internal temperature sensor data.
 * @param ICM42670_Handler Pointer to initialized ICM42670 hardware interface structure.
 * @param ICM42670_T_Data Pointer to structure to receive temperature data.
 * @retval ICM42670_Error_TypeDef Status of the read operation.
 */
ICM42670_Error_TypeDef ICM42670_T_Data_Read(ICM42670_HW_InitTypeDef *, ICM42670_Temp_Data_TypeDef *);

/**
 * @brief Read a single register from ICM42670 via SPI.
 * @param ICM42670_Handler Pointer to initialized ICM42670 hardware interface structure.
 * @param ICM42670_Register_Addr Address of the register to read.
 * @param pData Pointer to variable to receive the read value.
 * @retval ICM42670_Error_TypeDef Status of the read operation.
 */
ICM42670_Error_TypeDef ICM42670_SingleRegister_Read(ICM42670_HW_InitTypeDef *, uint8_t, uint8_t *);

/**
 * @brief Write a single byte to a register in the ICM42670 via SPI.
 * @param ICM42670_Handler Pointer to initialized ICM42670 hardware interface structure.
 * @param ICM42670_Register_Addr Address of the register to write.
 * @param ICM42670_Write_Data Data byte to write.
 * @retval ICM42670_Error_TypeDef Status of the write operation.
 */
ICM42670_Error_TypeDef ICM42670_SingleRegister_Write(ICM42670_HW_InitTypeDef *, uint8_t, uint8_t);

/**
 * @brief Pull chip select (CS) pin low to initiate SPI communication.
 * @param CS_GPIOport GPIO port of the CS pin.
 * @param CS_GPIOpin GPIO pin number.
 */
void enableCS_ICM42670(GPIO_TypeDef *, uint16_t);

/**
 * @brief Release chip select (CS) pin high to end SPI communication.
 * @param CS_GPIOport GPIO port of the CS pin.
 * @param CS_GPIOpin GPIO pin number.
 */
void disableCS_ICM42670(GPIO_TypeDef *, uint16_t);


void ICM44670_getData(void);
void ICM42670_init(void);

typedef struct ICM42670_struct{
	uint8_t	ID;
	ICM42670_Data_TypeDef accel_data;
	ICM42670_Data_TypeDef gyro_data;
	ICM42670_Temp_Data_TypeDef temp_data;

	float ax_g;
	float ay_g;
	float az_g;

	float gx_dps;
	float gy_dps;
	float gz_dps;

}ICM42670_t;

extern ICM42670_HW_InitTypeDef ICM42670_Handle;
extern ICM42670_t ICM42670;

#endif /* INC_ICM42670_H_ */
