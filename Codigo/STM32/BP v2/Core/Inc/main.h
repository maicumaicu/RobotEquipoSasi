/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#define CNY70_Pin GPIO_PIN_0
#define CNY70_GPIO_Port GPIOA
#define SHARP_D_Pin GPIO_PIN_1
#define SHARP_D_GPIO_Port GPIOA
#define SHARP_C_Pin GPIO_PIN_2
#define SHARP_C_GPIO_Port GPIOA
#define SHARP_I_Pin GPIO_PIN_3
#define SHARP_I_GPIO_Port GPIOA
#define BTN1_Pin GPIO_PIN_12
#define BTN1_GPIO_Port GPIOB
#define BTN2_Pin GPIO_PIN_13
#define BTN2_GPIO_Port GPIOB
#define BTN3_Pin GPIO_PIN_14
#define BTN3_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_15
#define LED_GPIO_Port GPIOB
#define BIN2_Pin GPIO_PIN_12
#define BIN2_GPIO_Port GPIOA
#define BIN1_Pin GPIO_PIN_15
#define BIN1_GPIO_Port GPIOA
#define STBY_Pin GPIO_PIN_3
#define STBY_GPIO_Port GPIOB
#define AIN1_Pin GPIO_PIN_4
#define AIN1_GPIO_Port GPIOB
#define AIN2_Pin GPIO_PIN_5
#define AIN2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
