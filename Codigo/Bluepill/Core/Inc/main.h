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
#include "motors.h"
#include "sharp.h"
//
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct {
	int Lados[4];
	int visitado;
	int final;
} Node;

typedef struct {
	int x;
	int y;
} Position;
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
int ChooseNextNode(int x, int y);
void EliminateNode(int x, int y);
void CreateNode(int x, int y);
int SearchAvailableNode(int x, int y);
void mainMachine();
void robotMachine();
void moveNode(int lado);
void rotateAxis(int direccion);
void resetAxis();
void movementMachine(int move);
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
#define MB1_Pin GPIO_PIN_6
#define MB1_GPIO_Port GPIOA
#define MB2_Pin GPIO_PIN_7
#define MB2_GPIO_Port GPIOA
#define PWMA_Pin GPIO_PIN_10
#define PWMA_GPIO_Port GPIOB
#define PWMB_Pin GPIO_PIN_11
#define PWMB_GPIO_Port GPIOB
#define BTN1_Pin GPIO_PIN_12
#define BTN1_GPIO_Port GPIOB
#define BTN2_Pin GPIO_PIN_13
#define BTN2_GPIO_Port GPIOB
#define BTN3_Pin GPIO_PIN_14
#define BTN3_GPIO_Port GPIOB
#define BIN2_Pin GPIO_PIN_11
#define BIN2_GPIO_Port GPIOA
#define BIN1_Pin GPIO_PIN_12
#define BIN1_GPIO_Port GPIOA
#define STBY_Pin GPIO_PIN_15
#define STBY_GPIO_Port GPIOA
#define AIN1_Pin GPIO_PIN_3
#define AIN1_GPIO_Port GPIOB
#define AIN2_Pin GPIO_PIN_4
#define AIN2_GPIO_Port GPIOB
#define MA2_Pin GPIO_PIN_6
#define MA2_GPIO_Port GPIOB
#define MA1_Pin GPIO_PIN_7
#define MA1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define BIN2 BIN2_GPIO_Port,BIN2_Pin
#define BIN1 BIN1_GPIO_Port,BIN1_Pin
#define STBY STBY_GPIO_Port,STBY_Pin
#define AIN1 AIN1_GPIO_Port,AIN1_Pin
#define AIN2 AIN2_GPIO_Port,AIN2_Pin
#define BTN1 BTN1_GPIO_Port,BTN1_Pin
#define BTN2 BTN2_GPIO_Port,BTN2_Pin
#define BTN3 BTN3_GPIO_Port , BTN3_Pin
#define LED LED_GPIO_Port, LED_Pin

#define MOTOR_A 0
#define MOTOR_B 1

#define ADELANTE 0
#define IZQUIERDA 1
#define ATRAS 2
#define DERECHA 3
#define SUPER 4
#define OFF 5

#define FORWARD_DISTANCE 250
#define LEFT_ANGLE_MIN 90
#define LEFT_ANGLE_MAX 96
#define FORWARD_VELOCITY_I 40
#define FORWARD_VELOCITY_D 47
#define TURN_VELOCITY_D 50
#define TURN_VELOCITY_I 50

#define ALTO 5
#define ANCHO 5
#define ancho ANCHO * 2
#define alto ALTO * 2

#define READING 0
#define CHOOSING 1
#define MOVING 2

#define SETUP 0
#define MAPPING 1
#define RESOLUTION 2
#define RACING 3

#define NEGRO 1
#define BLANCO 0

#define PARED 1
#define LIBRE 0

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
