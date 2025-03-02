/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
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
#define CIN1_Pin GPIO_PIN_7
#define CIN1_GPIO_Port GPIOF
#define CIN2_Pin GPIO_PIN_8
#define CIN2_GPIO_Port GPIOF
#define DIN1_Pin GPIO_PIN_9
#define DIN1_GPIO_Port GPIOF
#define DIN2_Pin GPIO_PIN_10
#define DIN2_GPIO_Port GPIOF
#define BIN2_Pin GPIO_PIN_0
#define BIN2_GPIO_Port GPIOC
#define BIN1_Pin GPIO_PIN_1
#define BIN1_GPIO_Port GPIOC
#define AIN1_Pin GPIO_PIN_4
#define AIN1_GPIO_Port GPIOA
#define AIN2_Pin GPIO_PIN_5
#define AIN2_GPIO_Port GPIOA
#define PWMT_Pin GPIO_PIN_6
#define PWMT_GPIO_Port GPIOA
#define BJ_Pin GPIO_PIN_7
#define BJ_GPIO_Port GPIOA
#define PWMA_Pin GPIO_PIN_9
#define PWMA_GPIO_Port GPIOE
#define PWMC_Pin GPIO_PIN_11
#define PWMC_GPIO_Port GPIOE
#define PWMD_Pin GPIO_PIN_13
#define PWMD_GPIO_Port GPIOE
#define PWMB_Pin GPIO_PIN_14
#define PWMB_GPIO_Port GPIOE
#define IN1_Pin GPIO_PIN_4
#define IN1_GPIO_Port GPIOG
#define IN2_Pin GPIO_PIN_6
#define IN2_GPIO_Port GPIOG
#define HW1_Pin GPIO_PIN_10
#define HW1_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
