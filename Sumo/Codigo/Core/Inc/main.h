/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "defines.h"
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
//void btnMachine(int index);
void mainMachine();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define P1_Pin GPIO_PIN_0
#define P1_GPIO_Port GPIOA
#define P2_Pin GPIO_PIN_1
#define P2_GPIO_Port GPIOA
#define P3_Pin GPIO_PIN_2
#define P3_GPIO_Port GPIOA
#define P4_Pin GPIO_PIN_3
#define P4_GPIO_Port GPIOA
#define P5_Pin GPIO_PIN_4
#define P5_GPIO_Port GPIOA
#define EN1_Pin GPIO_PIN_5
#define EN1_GPIO_Port GPIOA
#define INB1_Pin GPIO_PIN_7
#define INB1_GPIO_Port GPIOA
#define INA2_Pin GPIO_PIN_0
#define INA2_GPIO_Port GPIOB
#define INB2_Pin GPIO_PIN_10
#define INB2_GPIO_Port GPIOB
#define INA1_Pin GPIO_PIN_11
#define INA1_GPIO_Port GPIOB
#define S1_Pin GPIO_PIN_10
#define S1_GPIO_Port GPIOA
#define S2_Pin GPIO_PIN_11
#define S2_GPIO_Port GPIOA
#define B4_Pin GPIO_PIN_15
#define B4_GPIO_Port GPIOA
#define B3_Pin GPIO_PIN_3
#define B3_GPIO_Port GPIOB
#define B2_Pin GPIO_PIN_4
#define B2_GPIO_Port GPIOB
#define B1_Pin GPIO_PIN_5
#define B1_GPIO_Port GPIOB
#define L1_Pin GPIO_PIN_6
#define L1_GPIO_Port GPIOB
#define L2_Pin GPIO_PIN_7
#define L2_GPIO_Port GPIOB
#define L3_Pin GPIO_PIN_8
#define L3_GPIO_Port GPIOB
#define L4_Pin GPIO_PIN_9
#define L4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
//PINES
/*




#define S3 S3_GPIO_Port, S3_Pin
#define S4 S4_GPIO_Port, S4_Pin
#define S5 S5_GPIO_Port, S5_Pin
#define S6 S6_GPIO_Port, S6_Pin
#define S7 S7_GPIO_Port, S7_Pin
#define S8 S8_GPIO_Port, S8_Pin

*/
#define S1 S1_GPIO_Port, S1_Pin
#define S2 S2_GPIO_Port, S2_Pin
#define L1 L1_GPIO_Port, L1_Pin
#define L2 L2_GPIO_Port, L2_Pin
#define L3 L3_GPIO_Port, L3_Pin
#define L4 L4_GPIO_Port, L4_Pin
#define B1 B1_GPIO_Port, B1_Pin
#define B2 B2_GPIO_Port, B2_Pin
#define B3 B3_GPIO_Port, B3_Pin
#define B4 B4_GPIO_Port, B4_Pin
#define EN1 EN1_GPIO_Port, EN1_Pin

#define INB1 INB1_GPIO_Port, INB1_Pin
#define INB2 INB2_GPIO_Port, INB2_Pin
#define INA1 INA1_GPIO_Port, INA1_Pin
#define INA2 INA2_GPIO_Port, INA2_Pin
extern pin pinS[];
extern int Sensors[];
extern int inicio;



#define S38kh S38kh_GPIO_Port, S38kh_Pin
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
