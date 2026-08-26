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
#include "stm32h7xx_hal.h"

#include "stm32h7xx_nucleo.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
extern I2C_HandleTypeDef hi2c2;

#include <stdio.h>
#include <stdbool.h>
#include "I2CLCD.h"
#include "AS5600.h"
#include "MPU6050.h"
#include "IncEncoder.h"
#include "SPIEncoder.h"
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
#define Button_Pin GPIO_PIN_13
#define Button_GPIO_Port GPIOC
#define Button_EXTI_IRQn EXTI15_10_IRQn
#define EncMotorA_Pin GPIO_PIN_3
#define EncMotorA_GPIO_Port GPIOF
#define EncMotorA_EXTI_IRQn EXTI3_IRQn
#define GreenLED_Pin GPIO_PIN_0
#define GreenLED_GPIO_Port GPIOB
#define BournsEncA_Pin GPIO_PIN_9
#define BournsEncA_GPIO_Port GPIOE
#define BournsEncA_EXTI_IRQn EXTI9_5_IRQn
#define BournsEncB_Pin GPIO_PIN_11
#define BournsEncB_GPIO_Port GPIOE
#define BournsEncB_EXTI_IRQn EXTI15_10_IRQn
#define EMS22A_CLK_Pin GPIO_PIN_12
#define EMS22A_CLK_GPIO_Port GPIOE
#define EMS22A_MISO_Pin GPIO_PIN_13
#define EMS22A_MISO_GPIO_Port GPIOE
#define EMS22A_MOSI_Pin GPIO_PIN_14
#define EMS22A_MOSI_GPIO_Port GPIOE
#define RedLED_Pin GPIO_PIN_14
#define RedLED_GPIO_Port GPIOB
#define EMS22_2_CS_Pin GPIO_PIN_14
#define EMS22_2_CS_GPIO_Port GPIOD
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define EncMotorB_Pin GPIO_PIN_12
#define EncMotorB_GPIO_Port GPIOG
#define EncMotorB_EXTI_IRQn EXTI15_10_IRQn
#define EMS22_1_CS_Pin GPIO_PIN_5
#define EMS22_1_CS_GPIO_Port GPIOB
#define YellowLED_Pin GPIO_PIN_1
#define YellowLED_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
