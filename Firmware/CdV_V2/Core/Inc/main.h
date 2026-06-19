/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define System_LED_Pin GPIO_PIN_14
#define System_LED_GPIO_Port GPIOC
#define Armed_LED_Pin GPIO_PIN_15
#define Armed_LED_GPIO_Port GPIOC
#define PWM_CH2_Pin GPIO_PIN_1
#define PWM_CH2_GPIO_Port GPIOA
#define PWM_CH3_Pin GPIO_PIN_2
#define PWM_CH3_GPIO_Port GPIOA
#define PWM_CH4_Pin GPIO_PIN_3
#define PWM_CH4_GPIO_Port GPIOA
#define Memory_CS_Pin GPIO_PIN_4
#define Memory_CS_GPIO_Port GPIOA
#define Memory_SCK_Pin GPIO_PIN_5
#define Memory_SCK_GPIO_Port GPIOA
#define Memory_MISO_Pin GPIO_PIN_6
#define Memory_MISO_GPIO_Port GPIOA
#define Memory_MOSI_Pin GPIO_PIN_7
#define Memory_MOSI_GPIO_Port GPIOA
#define Memory_WP_Pin GPIO_PIN_4
#define Memory_WP_GPIO_Port GPIOC
#define Memory_RST_Pin GPIO_PIN_0
#define Memory_RST_GPIO_Port GPIOB
#define BME280_CS_Pin GPIO_PIN_12
#define BME280_CS_GPIO_Port GPIOB
#define ICM_CS_Pin GPIO_PIN_6
#define ICM_CS_GPIO_Port GPIOC
#define ICM_INT2_Pin GPIO_PIN_7
#define ICM_INT2_GPIO_Port GPIOC
#define ICM_INT_Pin GPIO_PIN_8
#define ICM_INT_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
