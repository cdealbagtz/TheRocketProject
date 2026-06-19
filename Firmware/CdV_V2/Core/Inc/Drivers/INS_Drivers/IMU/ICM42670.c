/*
 * ICM42670.c
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


#include "Drivers/INS_Drivers/IMU/ICM42670.h"




ICM42670_HW_InitTypeDef ICM42670_Handle = {
    .SPIhandler = &hspi2,             // Your SPI handle configured in your project
    .CS_GPIOport = GPIOC,             // GPIO port of CS pin
    .CS_GPIOpin = GPIO_PIN_6,         // GPIO pin of CS
    .SPI_Timeout = 100                // SPI timeout in milliseconds
};


ICM42670_t ICM42670;


/* Private SPI Handler */

void ICM42670_init(void){
	ICM42670_ID_Verify(&ICM42670_Handle);
	HAL_Delay(10);
	ICM42670_Set_Accelerometer(&ICM42670_Handle, ICM_A_ODR_1600, ICM_A_RANGE_16, ICM_A_LOW_NOISE_MODE);
	ICM42670_Set_Gyrometer(&ICM42670_Handle, ICM_G_ODR_1600, ICM_G_RANGE_0250, ICM_G_LOW_NOISE_MODE);

}

void ICM44670_getData(void){
	ICM42670_A_Data_Read(&ICM42670_Handle, &ICM42670.accel_data);
	ICM42670_G_Data_Read(&ICM42670_Handle, &ICM42670.gyro_data);
	ICM42670_T_Data_Read(&ICM42670_Handle, &ICM42670.temp_data);

	ICM42670.ax_g = (float)ICM42670.accel_data.axes.DX/ 2048.0f;
	ICM42670.ay_g = (float)ICM42670.accel_data.axes.DY/ 2048.0f;
	ICM42670.az_g = (float)ICM42670.accel_data.axes.DZ/ 2048.0f;

	ICM42670.gx_dps = (float)ICM42670.gyro_data.axes.DX / 131.07f;
	ICM42670.gy_dps = (float)ICM42670.gyro_data.axes.DY / 131.07f;
	ICM42670.gz_dps = (float)ICM42670.gyro_data.axes.DZ / 131.07f;
}



/**
 * @brief  Read the ICM42670 device ID and check if it matches the expected value
 * @note   Returns ICM_NO_ERROR only if content matches ICM_DEVICE_ID
 * @param  ICM42670_Handler Pointer to the ICM42670_HW_InitTypeDef structure
 * @retval ICM42670_Error_TypeDef Verification status
 */
ICM42670_Error_TypeDef ICM42670_ID_Verify(ICM42670_HW_InitTypeDef *ICM42670_Handler){
    uint8_t ID_Receive = 0;

    ICM42670_Error_TypeDef Verify_Status = ICM42670_SingleRegister_Read(ICM42670_Handler, ICM_WHO_AM_I, &ID_Receive);
    ICM42670.ID = ID_Receive;
    if ((ID_Receive == ICM_DEVICE_ID) && (Verify_Status == ICM_NO_ERROR))
        return ICM_NO_ERROR;
    else
        return ICM_ID_VERIFY_ERROR;
}

/**
 * @brief  Set accelerometer configuration: data rate, range and mode
 * @note   Uses ICM42670_SingleRegister_Write directly to write registers ICM_ACCEL_CONFIG0 and ICM_PWR_MGMT0
 * @param  ICM42670_Handler Pointer to the ICM42670_HW_InitTypeDef structure
 * @param  ICM42670_A_Rate 8-bit accelerometer data rate
 * @param  ICM42670_A_Range 8-bit accelerometer range
 * @param  ICM42670_A_Mode Power mode setting for accelerometer
 * @retval ICM42670_Error_TypeDef Status of the operation
 */
ICM42670_Error_TypeDef ICM42670_Set_Accelerometer(ICM42670_HW_InitTypeDef *ICM42670_Handler, uint8_t ICM42670_A_Rate, uint8_t ICM42670_A_Range, uint8_t ICM42670_A_Mode)
{
	uint8_t ICM_ACCEL_CONFIG0_Reg_Return = 0;
	uint8_t ICM_ACCEL_CONFIG0_Accel = (ICM42670_A_Rate | ICM42670_A_Range);

	uint8_t ICM_PWR_MGMT0_Reg_Return = 0;

	// Write accelerometer configuration
	ICM42670_SingleRegister_Write(ICM42670_Handler, ICM_ACCEL_CONFIG0 , ICM_ACCEL_CONFIG0_Accel);
	ICM42670_SingleRegister_Read(ICM42670_Handler, ICM_ACCEL_CONFIG0 , &ICM_ACCEL_CONFIG0_Reg_Return);

	// Read current power management register
	ICM42670_SingleRegister_Read(ICM42670_Handler, ICM_PWR_MGMT0 , &ICM_PWR_MGMT0_Reg_Return);

	uint8_t ICM_PWR_MGMT0_Accel = (ICM_PWR_MGMT0_Reg_Return | ICM42670_A_Mode);

	// Set accelerometer mode bits
	ICM42670_SingleRegister_Write(ICM42670_Handler, ICM_PWR_MGMT0 , ICM_PWR_MGMT0_Accel);
	ICM42670_SingleRegister_Read(ICM42670_Handler, ICM_PWR_MGMT0 , &ICM_PWR_MGMT0_Reg_Return);

	if( (ICM_ACCEL_CONFIG0_Reg_Return != ICM_ACCEL_CONFIG0_Accel) || ((ICM_PWR_MGMT0_Reg_Return & 0x03) != ICM42670_A_Mode))
		return ICM_INV_REG_DATA_READ;
	else
		return ICM_NO_ERROR;
}

/**
 * @brief  Set gyroscope configuration: data rate, range and mode
 * @note   Uses ICM42670_SingleRegister_Write directly to write registers ICM_GYRO_CONFIG0 and ICM_PWR_MGMT0
 * @param  ICM42670_Handler Pointer to the ICM42670_HW_InitTypeDef structure
 * @param  ICM42670_G_Rate 8-bit gyroscope data rate
 * @param  ICM42670_G_Range 8-bit gyroscope range
 * @param  ICM42670_G_Mode Power mode setting for gyroscope
 * @retval ICM42670_Error_TypeDef Status of the operation
 */
ICM42670_Error_TypeDef ICM42670_Set_Gyrometer(ICM42670_HW_InitTypeDef *ICM42670_Handler, uint8_t ICM42670_G_Rate, uint8_t ICM42670_G_Range, uint8_t ICM42670_G_Mode)
{
	uint8_t ICM_GYRO_CONFIG0_Reg_Return = 0;
	uint8_t ICM_GYRO_CONFIG0_Accel = (ICM42670_G_Rate | ICM42670_G_Range);

	uint8_t ICM_PWR_MGMT0_Reg_Return = 0;

	// Write gyroscope configuration
	ICM42670_SingleRegister_Write(ICM42670_Handler, ICM_GYRO_CONFIG0 , ICM_GYRO_CONFIG0_Accel);
	ICM42670_SingleRegister_Read(ICM42670_Handler, ICM_GYRO_CONFIG0 , &ICM_GYRO_CONFIG0_Reg_Return);

	// Read current power management register
	ICM42670_SingleRegister_Read(ICM42670_Handler, ICM_PWR_MGMT0 , &ICM_PWR_MGMT0_Reg_Return);

	// Set gyroscope mode bits
	uint8_t ICM_PWR_MGMT0_Accel = (ICM_PWR_MGMT0_Reg_Return | ICM42670_G_Mode);
	ICM42670_SingleRegister_Write(ICM42670_Handler, ICM_PWR_MGMT0 , ICM_PWR_MGMT0_Accel);
	ICM42670_SingleRegister_Read(ICM42670_Handler, ICM_PWR_MGMT0 , &ICM_PWR_MGMT0_Reg_Return);

	if( (ICM_GYRO_CONFIG0_Reg_Return != ICM_GYRO_CONFIG0_Accel) || ((ICM_PWR_MGMT0_Reg_Return & 0x0C) != ICM42670_G_Mode))
		return ICM_INV_REG_DATA_READ;
	else
		return ICM_NO_ERROR;
}

/**
 * @brief  Configure interrupts: INT1 for data ready
 * @note   Writes to ICM_INT_CONFIG and ICM_INT_SOURCE0. Clears status registers by reading output registers
 * @param  ICM42670_Handler Pointer to the ICM42670_HW_InitTypeDef structure
 * @retval ICM42670_Error_TypeDef Status of the operation
 */
ICM42670_Error_TypeDef ICM42670_Set_Interrupt_Measurement(ICM42670_HW_InitTypeDef *ICM42670_Handler){
	uint8_t ICM_INT_CONFIG_CTRL_REG_Return = 0;
	uint8_t ICM_ICM_INT_SOURCE0_REG_Return = 0;
	uint8_t ICM_OUTZ_H_REG_Return = 0;

	// Set INT1 to latched mode and active high
	uint8_t ICM_INT_CONFIG_Config = (ICM_INT1_ACTIVEHIGH | ICM_INT1_LATCHMODE);

	ICM42670_SingleRegister_Write(ICM42670_Handler, ICM_INT_CONFIG, ICM_INT_CONFIG);
	ICM42670_SingleRegister_Read(ICM42670_Handler, ICM_INT_CONFIG, &ICM_INT_CONFIG_CTRL_REG_Return);

	// Enable data ready interrupt
	ICM42670_SingleRegister_Write(ICM42670_Handler, ICM_INT_SOURCE0, ICM_INT_DATA_READY);
	ICM42670_SingleRegister_Read(ICM42670_Handler, ICM_INT_SOURCE0, &ICM_ICM_INT_SOURCE0_REG_Return);

	// Dummy reads to clear status
	ICM42670_SingleRegister_Read(ICM42670_Handler, ICM_OUTZ_H_A, &ICM_OUTZ_H_REG_Return);
	ICM42670_SingleRegister_Read(ICM42670_Handler, ICM_OUTZ_H_G, &ICM_OUTZ_H_REG_Return);

	if(ICM_INT_CONFIG_CTRL_REG_Return!= ICM_INT_CONFIG_Config ||  ICM_ICM_INT_SOURCE0_REG_Return != ICM_INT_DATA_READY)
		return ICM_INV_REG_DATA_READ;
	else
		return ICM_NO_ERROR;

}


/**
 * @brief  Read accelerometer data (X, Y, Z) using sequential SPI access
 * @note   Reads 6 bytes and stores them in ICM42670_Data_TypeDef
 * @param  ICM42670_Handler Pointer to the ICM42670_HW_InitTypeDef structure
 * @param  ICM42670_Data Pointer to the ICM42670_Data_TypeDef structure
 * @retval ICM42670_Error_TypeDef Status of the operation
 */
ICM42670_Error_TypeDef ICM42670_A_Data_Read(ICM42670_HW_InitTypeDef *ICM42670_Handler, ICM42670_Data_TypeDef *ICM42670_Data){
	uint8_t SPITransmitData_ICM;
	uint8_t ICM_Data_Reply[7];

	SPITransmitData_ICM = (ICM_Read_Command | ICM_A_DATA_ADDRESS_INIT);


	enableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
	if(HAL_SPI_Transmit(ICM42670_Handler->SPIhandler, &SPITransmitData_ICM, 1, ICM42670_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
		return ICM_HAL_ERROR;
	}
	if(HAL_SPI_Receive(ICM42670_Handler->SPIhandler, ICM_Data_Reply, 6, ICM42670_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
		return ICM_HAL_ERROR;
	}
	disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);


	ICM42670_Data->axes.DX =  (int16_t)((ICM_Data_Reply[0]<<8) |  ICM_Data_Reply[1]) - Config_Configuration.INS_ConfigPackage.INS_Config.ICM42670_Bias.ACC[0];
	ICM42670_Data->axes.DY =  (int16_t)((ICM_Data_Reply[2]<<8) |  ICM_Data_Reply[3]) - Config_Configuration.INS_ConfigPackage.INS_Config.ICM42670_Bias.ACC[1];
	ICM42670_Data->axes.DZ =  (int16_t)((ICM_Data_Reply[4]<<8) |  ICM_Data_Reply[5]) - Config_Configuration.INS_ConfigPackage.INS_Config.ICM42670_Bias.ACC[2];

	return ICM_NO_ERROR;
}

/**
 * @brief  Read gyroscope data (X, Y, Z) using sequential SPI access
 * @note   Reads 6 bytes and stores them in ICM42670_Data_TypeDef
 * @param  ICM42670_Handler Pointer to the ICM42670_HW_InitTypeDef structure
 * @param  ICM42670_Data Pointer to the ICM42670_Data_TypeDef structure
 * @retval ICM42670_Error_TypeDef Status of the operation
 */
ICM42670_Error_TypeDef ICM42670_G_Data_Read(ICM42670_HW_InitTypeDef *ICM42670_Handler, ICM42670_Data_TypeDef *ICM42670_Data){
	uint8_t SPITransmitData_ICM;
	uint8_t ICM_Data_Reply[7];

	SPITransmitData_ICM = (ICM_Read_Command | ICM_G_DATA_ADDRESS_INIT);

	enableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
	if(HAL_SPI_Transmit(ICM42670_Handler->SPIhandler, &SPITransmitData_ICM, 1, ICM42670_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
		return ICM_HAL_ERROR;
	}
	if(HAL_SPI_Receive(ICM42670_Handler->SPIhandler, ICM_Data_Reply, 6, ICM42670_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
		return ICM_HAL_ERROR;
	}
	disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);

	ICM42670_Data->axes.DX =  (int16_t)((ICM_Data_Reply[0]<<8) |  ICM_Data_Reply[1]) - Config_Configuration.INS_ConfigPackage.INS_Config.ICM42670_Bias.Gy[0];
	ICM42670_Data->axes.DY =  (int16_t)((ICM_Data_Reply[2]<<8) |  ICM_Data_Reply[3]) - Config_Configuration.INS_ConfigPackage.INS_Config.ICM42670_Bias.Gy[1];
	ICM42670_Data->axes.DZ =  (int16_t)((ICM_Data_Reply[4]<<8) |  ICM_Data_Reply[5]) - Config_Configuration.INS_ConfigPackage.INS_Config.ICM42670_Bias.Gy[2];

	return ICM_NO_ERROR;
}

/**
 * @brief  Read internal temperature using sequential SPI access
 * @note   Reads 2 bytes and stores them in ICM42670_Temp_Data_TypeDef
 * @param  ICM42670_Handler Pointer to the ICM42670_HW_InitTypeDef structure
 * @param  ICM42670_T_Data Pointer to the ICM42670_Temp_Data_TypeDef structure
 * @retval ICM42670_Error_TypeDef Status of the operation
 */
ICM42670_Error_TypeDef ICM42670_T_Data_Read(ICM42670_HW_InitTypeDef *ICM42670_Handler, ICM42670_Temp_Data_TypeDef *ICM42670_T_Data){
	uint8_t SPITransmitData_ICM;
	uint8_t ICM_Data_Reply[3];

	SPITransmitData_ICM = (ICM_Read_Command | ICM_T_DATA_ADDRESS_INIT);

	enableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
	if(HAL_SPI_Transmit(ICM42670_Handler->SPIhandler, &SPITransmitData_ICM, 1, ICM42670_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
		return ICM_HAL_ERROR;
	}
	if(HAL_SPI_Receive(ICM42670_Handler->SPIhandler, ICM_Data_Reply, 2, ICM42670_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
		return ICM_HAL_ERROR;
	}
	disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);

	ICM42670_T_Data->temp.T = (int16_t)((ICM_Data_Reply[0] << 8) | ICM_Data_Reply[1]);

	return ICM_NO_ERROR;
}


/**
 * @brief  Write a single byte to a register of the ICM42670
 * @note   The function uses SPI with manual chip select control
 * @param  ICM42670_Handler Pointer to the ICM42670_HW_InitTypeDef structure
 * @param  ICM42670_Register_Addr Address of the target register
 * @param  ICM42670_Write_Data Data byte to write into the register
 * @retval ICM42670_Error_TypeDef Status of the operation
 */
ICM42670_Error_TypeDef ICM42670_SingleRegister_Write(ICM42670_HW_InitTypeDef *ICM42670_Handler, uint8_t ICM42670_Register_Addr, uint8_t ICM42670_Write_Data)
{
	uint8_t SPITransmitData_ICM;
	SPITransmitData_ICM = (ICM_Write_command | ICM42670_Register_Addr);

	enableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
	if(HAL_SPI_Transmit(ICM42670_Handler->SPIhandler, &SPITransmitData_ICM, 1, ICM42670_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
		return ICM_HAL_ERROR;
	}
	if(HAL_SPI_Transmit(ICM42670_Handler->SPIhandler, &ICM42670_Write_Data, 1, ICM42670_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
		return ICM_HAL_ERROR;
	}
	disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);

	return ICM_NO_ERROR;
}

/**
 * @brief  Read a single byte from a register of the ICM42670
 * @note   The function uses SPI with manual chip select control
 * @param  ICM42670_Handler Pointer to the ICM42670_HW_InitTypeDef structure
 * @param  ICM42670_Register_Addr Address of the target register
 * @param  pData Pointer to store the read data byte
 * @retval ICM42670_Error_TypeDef Status of the operation
 */
ICM42670_Error_TypeDef ICM42670_SingleRegister_Read(ICM42670_HW_InitTypeDef *ICM42670_Handler, uint8_t ICM42670_Register_Addr, uint8_t *pData)
{
	uint8_t SPITransmitData_ICM;
	SPITransmitData_ICM = (ICM_Read_Command | ICM42670_Register_Addr);

	enableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
	if(HAL_SPI_Transmit(ICM42670_Handler->SPIhandler, &SPITransmitData_ICM, 1, ICM42670_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
		return ICM_HAL_ERROR;
	}
	if(HAL_SPI_Receive(ICM42670_Handler->SPIhandler, pData, 1, ICM42670_Handler->SPI_Timeout) != HAL_OK)
	{
		disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);
		return ICM_HAL_ERROR;
	}
	disableCS_ICM42670(ICM42670_Handler->CS_GPIOport, ICM42670_Handler->CS_GPIOpin);

	return ICM_NO_ERROR;
}

/**
 * @brief  Enable chip select (CS) for the ICM42670 (active low)
 * @param  CS_GPIOport Pointer to the GPIO port used for CS
 * @param  CS_GPIOpin GPIO pin used for CS
 * @retval None
 */
void enableCS_ICM42670(GPIO_TypeDef *CS_GPIOport, uint16_t CS_GPIOpin){
  HAL_GPIO_WritePin(CS_GPIOport, CS_GPIOpin, GPIO_PIN_RESET);
}

/**
 * @brief  Disable chip select (CS) for the ICM42670 (inactive high)
 * @param  CS_GPIOport Pointer to the GPIO port used for CS
 * @param  CS_GPIOpin GPIO pin used for CS
 * @retval None
 */
void disableCS_ICM42670(GPIO_TypeDef *CS_GPIOport, uint16_t CS_GPIOpin){
  HAL_GPIO_WritePin(CS_GPIOport, CS_GPIOpin, GPIO_PIN_SET);
}


