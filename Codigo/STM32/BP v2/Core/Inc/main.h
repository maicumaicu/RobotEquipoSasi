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
typedef struct {
	int Lados[4];
	int visitado;
	int final;
	int distance;
} Node;

typedef struct {
	int x;
	int y;
} Position;

typedef struct {
	GPIO_TypeDef *Port;
	uint16_t pin;
	int estado;
	int flag;
} button;
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

extern float KPTchoice[];
extern float KDTchoice[];
extern float KPAchoice[];
extern float KDAchoice[];
extern float KPPchoice[];
extern float KDPchoice[];
extern float velocityChoice[];
extern int baseChoice[];
extern int forwardChoice[];
extern int RightChoice[];
extern int LeftChoice[];
extern float Sensors[];
extern float maxDistance[];
extern float offset;
extern int movementState;
extern int movimientoFlag;
extern int StraightFlag;
extern int xSpeed;
extern int objectiveDistance;
extern float tiempoDelay;
extern float KPT, KDT, KPA, KDA, KPP, KDP;
extern float velocity;
extern int choice;
extern float CenterDistanceRight, CenterDistanceLeft, MaxRightDistance,
MaxLeftDistance, MaxCenterDistance;
extern int objectiveDistance,acelerationObjective,aceleration,direction;

int ChooseNextNode(int x, int y);
int SearchAvailableNode(int x, int y);
void mainMachine();
void robotMachine();
/*void rotateAxis(int direccion);
void resetAxis();*/
//void movementMachine(int move);
void moveStraight();
void addDirection(int x, int y);
void intUartSend(float entero);
void runDirections(char moves[25]);
void btnMachine(int index);
void calibrateMachine();
void PrintMap();
void save_to_flash(uint8_t *data, uint32_t address);
void read_flash(uint8_t* data,uint32_t address);//Elección de constante proporcional del PID
uint32_t MAP(uint32_t au32_IN, uint32_t au32_INmin, uint32_t au32_INmax,
		uint32_t au32_OUTmin, uint32_t au32_OUTmax);
int constrain(int x, int a, int b);
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
#define BIN2 BIN2_GPIO_Port,BIN2_Pin
#define BIN1 BIN1_GPIO_Port,BIN1_Pin
#define STBY STBY_GPIO_Port,STBY_Pin
#define AIN1 AIN1_GPIO_Port,AIN1_Pin
#define AIN2 AIN2_GPIO_Port,AIN2_Pin
#define BTN1 BTN1_GPIO_Port,BTN1_Pin
#define BTN2 BTN2_GPIO_Port,BTN2_Pin
#define BTN3 BTN3_GPIO_Port , BTN3_Pin
#define LED LED_GPIO_Port, LED_Pin

#define CANT_BTN 3
#define ESPERA 0
#define CONFIRMACION 1
#define LIBERACION 2
#define TICKS_BTN  25

#define MOTOR_A 0
#define MOTOR_B 1

#define SLOW 0
#define FAST 1
#define TURN_90 2

#define ADELANTE 0
#define IZQUIERDA 1
#define ATRAS 2
#define DERECHA 3
#define SUPER 4
#define OFF 5

#define CENTER 0
#define LEFT 1
#define RIGHT 2
#define FORWARD 3

#define FORWARD_DISTANCE 230
#define LEFT_ANGLE_MIN 90
#define LEFT_ANGLE_MAX 96
#define FORWARD_VELOCITY_I 40
#define FORWARD_VELOCITY_D 47
#define TURN_VELOCITY_D 50
#define TURN_VELOCITY_I 50

#define ALTO 8
#define ANCHO 8
#define ancho ANCHO * 2
#define alto ALTO * 2

#define READING 0
#define CHOOSING 1
#define MOVING 2

#define SETUP 0
#define MAPPING 1
#define RESOLUTION 2
#define RACING 3
#define CALIBRATE 4

#define NEGRO 1
#define BLANCO 0

#define PARED 1
#define LIBRE 0

#define SETPOINT 8
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
