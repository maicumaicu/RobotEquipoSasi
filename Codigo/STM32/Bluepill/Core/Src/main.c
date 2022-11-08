/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sharp.h"
#include "motors.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "math.h"
#include <float.h>
#include <string.h>
#include "FLASH_PAGE_F1.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADC_BUF_LEN 1024
#define FLASH_STORAGE_M 0x08005000
#define FLASH_STORAGE_Q 0x08005500
#define page_size 0x800
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t adc_buf[ADC_BUF_LEN];
uint32_t CNY70[10];
uint32_t SHARP_1[10];
uint32_t SHARP_2[10];
uint32_t SHARP_3[10];
static float Sensors[4];
int direcciones[4];
uint8_t serialBuf[100];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int calState, CenterDistanceRight, CenterDistanceLeft, MaxRightDistance,
		MaxLeftDistance, MaxCenterDistance;
int powerA;
int powerB;
int ticks, lecturaBtn;
uint8_t RX_BUFFER[1] = { 0 };
uint8_t TX_BUFFER[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
float KP, KD, tiempoDelay;
float velocity;
long ticksNow;
int RightTick = 500;
int LeftTick = 500;
int ForwardTick = 400;
float KPchoice[2] = { 80, 80 }; //17                           //Elección de constante proporcional del PID
float KDchoice[2] = { 5, 4 }; //0.5                          //Elección de constante derivada del PID
float velocityChoice[2] = { 1000, 1000 };
int baseChoice[2] = { 15000, 20000 }; //150
int forwardChoice[2] = { 280, 290 };
int RightChoice[2] = { 160, 155 };
int LeftChoice[2] = { 155, 155 };
int TimerForward[2] = { 400, 200 };
int TimerRight[2] = { 200, 200 };
int TimerLeft[2] = { 200, 200 };
int choice;
int c, m, directionsSize, movimiento;
int finishFlag, movimientoFlag;
int valueCNY;
int direcciones[4];
int offset;
int counter;
int tick;
button btns[CANT_BTN];

int mainState = SETUP;
int robotState = READING;
int movementState = OFF;
char directions[25];
uint32_t Rx_Data[26];
char string[100];
int directionsSize;
Position actual;
Position last;
Node Map[alto][ancho];
float error, pid, previousError, elapsedTime, timeNow, timePrev, pidP, pidD;
int motLeft, motRight;
int q, F;
/*Position visual;
 Node VisualMap[ALTO][ANCHO];*/
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	btns[0].Port = BTN1_GPIO_Port;
	btns[0].pin = BTN1_Pin;
	btns[0].estado = ESPERA;
	btns[0].flag = 0;
	btns[1].Port = BTN2_GPIO_Port;
	btns[1].pin = BTN2_Pin;
	btns[1].estado = ESPERA;
	btns[1].flag = 0;
	btns[2].Port = BTN3_GPIO_Port;
	btns[2].pin = BTN3_Pin;
	btns[2].estado = ESPERA;
	btns[2].flag = 0;
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	HAL_GPIO_WritePin(STBY, GPIO_PIN_SET);
	TIM2->CCR3 = 15000;
	TIM2->CCR4 = 15000;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adc_buf, ADC_BUF_LEN);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
	TIM3->CNT = 0;
	TIM4->CNT = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		mainMachine();
		//intUartSend((int) calcularDistancia(TIM3->CNT) >> 1);
		/*runMotor(ADELANTE, MOTOR_A);
		 runMotor(ADELANTE, MOTOR_B);
		 intUartSend(TIM4->CNT);*/
		btnMachine(0);
		btnMachine(1);
		btnMachine(2);
		//intUartSend(Sensors[0]);
		//intUartSend(Sensors[1]);
		//intUartSend(Sensors[3]);

		/*HAL_GetTick()
		 * int d = calcularDistancia(TIM4->CNT);
		 if (calcularDistancia(TIM4->CNT) < 100) {


		 } else {
		 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
		 runMotor(OFF, MOTOR_A);
		 runMotor(OFF, MOTOR_B);
		 }*/
		//sprintf(MSG, TIM4->CNT);
		//runForward();
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void intUartSend(int entero) {

	int m;
	int c;
	int d;
	int u;

	m = entero / 1000;
	c = entero / 100 - m * 10;
	d = entero / 10 - (m * 100 + c * 10);
	u = entero - (m * 1000 + c * 100 + d * 10);

	TX_BUFFER[0] = m + '0';
	TX_BUFFER[1] = c + '0';
	TX_BUFFER[2] = d + '0';
	TX_BUFFER[3] = u + '0';
	TX_BUFFER[4] = '\n';
	HAL_UART_Transmit(&huart1, TX_BUFFER, 5, 100);
}

void mainMachine() {
	switch (mainState) {
	case SETUP:
		actual.x = ALTO;
		actual.y = ANCHO;
		/*visual.x = 0;
		 visual.y = 0;*/
		resetAxis();
		movimientoFlag = 0;
		finishFlag = 0;
		if (abs(Sensors[1] - Sensors[3]) < 0.5) {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		} else {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		}
		if (btns[0].flag == 1) {
			// Set The LED ON!
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			choice = SLOW;
			velocity = velocityChoice[SLOW];
			TIM2->CCR3 = baseChoice[SLOW];
			TIM2->CCR4 = baseChoice[SLOW];
			KP = KPchoice[SLOW];
			KD = KDchoice[SLOW];
			if (q == 0) {
				mainState = CALIBRATE;
				q++;
			} else {
				mainState = MAPPING;
			}

		}
		if (btns[1].flag == 1) {
			// Set The LED ON!
			choice = FAST;
			velocity = velocityChoice[FAST];
			TIM2->CCR3 = baseChoice[FAST];
			TIM2->CCR4 = baseChoice[FAST];
			KP = KPchoice[FAST];
			KD = KDchoice[FAST];
			mainState = RACING;
			Flash_Read_Data(0x0801FC00, Rx_Data, 2);
			Convert_To_Str(Rx_Data, string);
			//directions = ReadRun();
			//ShowRun();
		}
		if (btns[2].flag == 1) {
			// Set The LED ON!
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			choice = FAST;
			velocity = velocityChoice[FAST];
			TIM2->CCR3 = baseChoice[FAST];
			TIM2->CCR4 = baseChoice[FAST];
			KP = KPchoice[FAST];
			KD = KDchoice[FAST];
			if (q == 0) {
				mainState = CALIBRATE;
				q++;
			} else {
				mainState = MAPPING;
			}
		}
		//confirmacionCentrado();
		break;
	case CALIBRATE:
		calibrateMachine();
		//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		break;
	case MAPPING:
		if (finishFlag == 0) {
			robotMachine();
			/*TX_BUFFER[0] = 'L';
			 HAL_UART_Transmit(&huart1, TX_BUFFER, sizeof(TX_BUFFER), 100);*/
		} else {
			TX_BUFFER[0] = 'X';
			HAL_UART_Transmit(&huart1, TX_BUFFER, 1, 100);
			intUartSend(actual.x);
			TX_BUFFER[0] = 'Y';
			HAL_UART_Transmit(&huart1, TX_BUFFER, 1, 100);
			intUartSend(actual.y);
			actual.x = ALTO;
			actual.y = ANCHO;
			//visual.x = 0;
			//visual.y = 0;
			finishFlag = 0;
			resetAxis();
			PrintMap();
			mainState = RESOLUTION;
		}
		break;
	case RESOLUTION:
		if (Map[actual.x][actual.y].final == 0) {
			addDirection(actual.x, actual.y);
			TX_BUFFER[0] = 'X';
			HAL_UART_Transmit(&huart1, TX_BUFFER, 1, 100);
			intUartSend(actual.x);
			TX_BUFFER[0] = 'Y';
			HAL_UART_Transmit(&huart1, TX_BUFFER, 1, 100);
			intUartSend(actual.y);
		} else {
			//directions = optimizeDirections(directions);
			//SerialBT.println(directions);
			// UploadRun(directions);
			directions[directionsSize] = 'o';
			Flash_Write_Data(0x0801FC00, (uint32_t*) directions, 25);
			mainState = SETUP;
		}

		break;
	case RACING:
		runDirections(string);
		break;
	}

}

void calibrateMachine() {
	switch (calState) {
	case CENTER:
		intUartSend(abs(Sensors[1] - Sensors[3]));
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		if (btns[0].flag == 1) {
			CenterDistanceRight = Sensors[3];
			CenterDistanceLeft = Sensors[1];
			calState = LEFT;
		}
		if (abs(Sensors[1] - Sensors[3]) < 0.5) {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

		}
		break;
	case LEFT:
		intUartSend(abs(Sensors[3]));
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		if (btns[0].flag == 1) {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			MaxLeftDistance = Sensors[3] + 2;
			calState = RIGHT;
		}
		break;
	case RIGHT:
		intUartSend(abs(Sensors[1]));
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		if (btns[0].flag == 1) {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			MaxRightDistance = Sensors[1] + 2;
			calState = FORWARD;
		}
		break;
	case FORWARD:
		intUartSend(abs(Sensors[2]));
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		if (btns[0].flag == 1) {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			MaxCenterDistance = Sensors[2] + 2;
			mainState = SETUP;
			calState = CENTER;
		}
		break;
	}
}

void robotMachine() {
	switch (robotState) {
	case READING:
		HAL_Delay(10);
		TX_BUFFER[0] = 'X';
		TX_BUFFER[1] = actual.x + '0';
		TX_BUFFER[2] = '\n';
		TX_BUFFER[3] = 'Y';
		TX_BUFFER[4] = actual.y + '0';
		TX_BUFFER[5] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 6, 100);
		Map[actual.x][actual.y].visitado++;
		if (Map[actual.x][actual.y].visitado == 1) {
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			CreateNode(actual.x, actual.y);
			if(actual.x == ALTO && actual.y == ANCHO){
				Map[actual.x][actual.y].Lados[ATRAS] = 1;
			}
		}
		intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);
		/*TX_BUFFER[0] = 'D';
		 TX_BUFFER[1] = Map[actual.x][actual.y].Lados[DERECHA] + '0';
		 TX_BUFFER[2] = '\n';
		 TX_BUFFER[3] = 'C';
		 TX_BUFFER[4] = Map[actual.x][actual.y].Lados[ADELANTE] + '0';
		 TX_BUFFER[5] = '\n';
		 TX_BUFFER[6] = 'I';
		 TX_BUFFER[7] = Map[actual.x][actual.y].Lados[IZQUIERDA] + '0';
		 TX_BUFFER[8] = '\n';
		 TX_BUFFER[9] = 'A';
		 TX_BUFFER[10] = Map[actual.x][actual.y].Lados[ATRAS] + '0';
		 TX_BUFFER[11] = '\n';
		 HAL_UART_Transmit(&huart1, TX_BUFFER, 12, 100);
		 */
		valueCNY = Sensors[0];
		if (valueCNY == BLANCO) {
			Map[actual.x][actual.y].final = 1;
			finishFlag = 1;
		} else {
			Map[actual.x][actual.y].final = 0;
			robotState = CHOOSING;
		}
		//PrintMap();
		//HAL_Delay(1000);
		break;
	case CHOOSING:
		movimiento = ChooseNextNode(actual.x, actual.y);
		TX_BUFFER[0] = 'M';
		TX_BUFFER[1] = movimiento + '0';
		TX_BUFFER[2] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 3, 100);

		TX_BUFFER[0] = '*';
		TX_BUFFER[1] = '*';
		TX_BUFFER[2] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 3, 100);
		movimientoFlag = 0;
		ticksNow = HAL_GetTick();
		robotState = MOVING;

		break;
	case MOVING:
		//TX_BUFFER[0] = 'M';
		//HAL_UART_Transmit(&huart1, TX_BUFFER, sizeof(TX_BUFFER), 100);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		movementMachine(movimiento);

		if (movimientoFlag == 1) {
			robotState = READING;
		}
		break;
	}
}

void runDirections(char moves[100]) {
	if (moves[m] == 'a') {
		movementMachine(ADELANTE);
	} else if (moves[m] == 'd') {
		movementMachine(DERECHA);
	} else if (moves[m] == 'i') {
		movementMachine(IZQUIERDA);
	} else if (moves[m] == 'o') {
		movementMachine(OFF);
	} else {
		movementMachine(SUPER);
	}
	TX_BUFFER[0] = moves[m];
	HAL_UART_Transmit(&huart1, TX_BUFFER, 1, 100);
	if (movimientoFlag == 1) {
		m++;
		movimientoFlag = 0;
	}
}

void addDirection(int x, int y) {
	if (Map[x][y].Lados[direcciones[ADELANTE]] != 1) {
		//Map[x][y].Lados[direcciones[ADELANTE]] = 2;
		moveNode(direcciones[ADELANTE]);
		directions[directionsSize] = 'a';
	} else if (Map[x][y].Lados[direcciones[IZQUIERDA]] != 1) {
		//Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
		moveNode(direcciones[IZQUIERDA]);
		rotateAxis(IZQUIERDA);
		directions[directionsSize] = 'i';
	} else if (Map[x][y].Lados[direcciones[DERECHA]] != 1) {
		//Map[x][y].Lados[direcciones[DERECHA]] = 2;
		moveNode(direcciones[DERECHA]);
		rotateAxis(DERECHA);
		directions[directionsSize] = 'd';
	}
	/*intUartSend(Map[x][y].Lados[direcciones[ADELANTE]]);
	intUartSend(Map[x][y].Lados[direcciones[IZQUIERDA]]);
	intUartSend(Map[x][y].Lados[direcciones[DERECHA]]);*/
	TX_BUFFER[0] = 'D';
	TX_BUFFER[1] = directions[directionsSize];
	TX_BUFFER[2] = '\n';
	HAL_UART_Transmit(&huart1, TX_BUFFER, 3, 100);
	directionsSize++;
}

int ChooseNextNode(int x, int y) {
	if (Map[x][y].Lados[direcciones[ADELANTE]] == 0) {
		TX_BUFFER[0] = 'A';
		TX_BUFFER[1] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 2, 100);
		Map[x][y].Lados[direcciones[ADELANTE]] = 2;
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
			intUartSend(5000);
		}
		if (Map[x][y].Lados[direcciones[ATRAS]] != 1)
			Map[x][y].Lados[direcciones[ATRAS]] = 2;
		last.x = actual.x;
		last.y = actual.y;
		/*intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);*/
		moveNode(direcciones[ADELANTE]);
		return ADELANTE;
	} else if (Map[x][y].Lados[direcciones[IZQUIERDA]] == 0) {
		TX_BUFFER[0] = 'I';
		TX_BUFFER[1] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 2, 100);
		Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
			intUartSend(5000);
		}
		if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
			Map[x][y].Lados[direcciones[ATRAS]] = 2;
		}
		last.x = actual.x;
		last.y = actual.y;
		/*intUartSend(Map[x][y].Lados[DERECHA]);
		intUartSend(Map[x][y].Lados[ADELANTE]);
		intUartSend(Map[x][y].Lados[IZQUIERDA]);
		intUartSend(Map[x][y].Lados[ATRAS]);*/
		moveNode(direcciones[IZQUIERDA]);
		rotateAxis(IZQUIERDA);
		return IZQUIERDA;
	} else if (Map[x][y].Lados[direcciones[DERECHA]] == 0) {
		TX_BUFFER[0] = 'D';
		TX_BUFFER[1] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 2, 100);

		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
			intUartSend(5000);
		}
		Map[x][y].Lados[direcciones[DERECHA]] = 2;
		if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
			intUartSend(Map[x][y].Lados[direcciones[ATRAS]]);
			Map[x][y].Lados[direcciones[ATRAS]] = 2;
		}
		last.x = actual.x;
		last.y = actual.y;
		/*intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);*/
		moveNode(direcciones[DERECHA]);
		rotateAxis(DERECHA);
		return DERECHA;
	} else {
		TX_BUFFER[0] = 'O';
		TX_BUFFER[1] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 2, 100);
		return SearchAvailableNode(x, y);
	}

}
void EliminateNode(int x, int y) {
//Serial.println("Borro");
	Map[x][y].Lados[direcciones[ATRAS]] = 1;
	Map[last.x][last.y].visitado = 0;
}

int SearchAvailableNode(int x, int y) {
	if (Map[x][y].Lados[direcciones[ADELANTE]] != 1) {
		//Serial.println("Adelante1");

		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
			intUartSend(4000);
		}
		last.x = actual.x;
		last.y = actual.y;
		/*intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);*/
		moveNode(direcciones[ADELANTE]);

		return ADELANTE;
	} else if (Map[x][y].Lados[direcciones[IZQUIERDA]] != 1) {
		//Serial.println("IZQUIERDA1");l
		//moveNode(IZQUIERDA);
		//rotateAxis(IZQUIERDA);
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
			intUartSend(4000);
		}
		last.x = actual.x;
		last.y = actual.y;
		/*intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);*/
		moveNode(direcciones[IZQUIERDA]);

		rotateAxis(IZQUIERDA);
		return IZQUIERDA;
	} else if (Map[x][y].Lados[direcciones[DERECHA]] != 1) {
		//Serial.println("DERECHA1");
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
			intUartSend(4000);
		}
		last.x = actual.x;
		last.y = actual.y;
		/*intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);*/
		moveNode(direcciones[DERECHA]);
		rotateAxis(DERECHA);
		return DERECHA;
	} else if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
		last.x = actual.x;
		last.y = actual.y;
		/*intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);*/
		moveNode(direcciones[ATRAS]);

		rotateAxis(DERECHA);
		rotateAxis(DERECHA);
		return ATRAS;
	}
	return 0;
}
void moveNode(int lado) {
	switch (lado) {
	case ADELANTE:
		//if (visual.y != ALTO - 1) {
		actual.y++;
		//visual.y++;
		//}
		break;
	case IZQUIERDA:
		//if (visual.x != 0) {
		actual.x--;
		//visual.x--;
		//}
		break;
	case DERECHA:
		// if (visual.x != ANCHO - 1) {
		actual.x++;
		// visual.x++;
		// }
		break;
	case ATRAS:
		// if (visual.y != 0) {
		actual.y--;
		// visual.y--;
		// }

		break;
	}
}

/*void movementMachine(int move) {
 switch (movementState) {
 case OFF:
 runMotor(OFF, MOTOR_A);
 runMotor(OFF, MOTOR_B);
 if (move != OFF) {
 movementState = move;
 TIM3->CNT = 0;
 TIM4->CNT = 0;
 }
 break;
 case ADELANTE:
 tick = HAL_GetTick();
 intUartSend(tick);
 if (ticksNow + TimerForward[choice] > tick) {
 moveStraight();
 runMotor(ADELANTE, MOTOR_A);
 runMotor(ADELANTE, MOTOR_B);
 } else {
 movimientoFlag = 1;
 movementState = OFF;
 runMotor(OFF, MOTOR_A);
 runMotor(OFF, MOTOR_B);
 TIM3->CNT = 0;
 TIM4->CNT = 0;
 offset = 0;
 }
 break;
 case IZQUIERDA:
 tick = HAL_GetTick();
 TIM2->CCR3 = baseChoice[choice];
 TIM2->CCR4 = baseChoice[choice];
 if (ticksNow + TimerLeft[choice] > tick) {
 runMotor(ATRAS, MOTOR_A);
 runMotor(ADELANTE, MOTOR_B);
 } else {
 movementState = ADELANTE;
 ticksNow = HAL_GetTick();
 runMotor(OFF, MOTOR_A);
 runMotor(OFF, MOTOR_B);
 TIM3->CNT = 0;
 TIM4->CNT = 0;
 offset = 30;
 }
 break;
 case DERECHA:
 tick = HAL_GetTick();
 TIM2->CCR3 = baseChoice[choice];
 TIM2->CCR4 = baseChoice[choice];
 if (ticksNow + TimerRight[choice] > tick) {
 runMotor(ADELANTE, MOTOR_A);
 runMotor(ATRAS, MOTOR_B);
 } else {
 movementState = ADELANTE;
 ticksNow = HAL_GetTick();
 runMotor(OFF, MOTOR_A);
 runMotor(OFF, MOTOR_B);
 TIM3->CNT = 0;
 TIM4->CNT = 0;
 offset = 30;
 }
 break;
 case ATRAS:
 tick = HAL_GetTick();
 TIM2->CCR3 = baseChoice[choice];
 TIM2->CCR4 = baseChoice[choice];
 if (ticksNow + TimerRight[choice] * 2 > tick) {
 runMotor(ADELANTE, MOTOR_A);
 runMotor(ATRAS, MOTOR_B);
 } else {
 ticksNow = HAL_GetTick();
 movementState = ADELANTE;
 runMotor(OFF, MOTOR_A);
 runMotor(OFF, MOTOR_B);
 TIM3->CNT = 0;
 TIM4->CNT = 0;
 offset = 30;
 }
 break;
 }
 }*/
void movementMachine(int move) {
	switch (movementState) {
	case OFF:
		runMotor(OFF, MOTOR_A);
		runMotor(OFF, MOTOR_B);
		if (move != OFF) {
			movementState = move;
			TIM3->CNT = 0;
			TIM4->CNT = 0;
			if(Sensors[3] > Sensors[1]){
				F = 1 ;
			}else {
				F = 0;
			}
			//intUartSend(TIM3->CNT);
		}
		break;
	case ADELANTE:
		//intUartSend((int) calcularDistancia(TIM3->CNT));
		if ((calcularDistancia((TIM3->CNT >> 1)) < forwardChoice[choice])
				|| (calcularDistancia((TIM4->CNT >> 1)) < forwardChoice[choice]) /*&& Sensors[2] > 5*/) {
			moveStraight();
			runMotor(ADELANTE, MOTOR_A);
			runMotor(ADELANTE, MOTOR_B);
		} else {
			movimientoFlag = 1;
			movementState = OFF;
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			TIM3->CNT = 0;
			TIM4->CNT = 0;
			offset = 0;
			//intUartSend(10);
		}
		break;
	case IZQUIERDA:
		TIM2->CCR3 = baseChoice[choice];
		TIM2->CCR4 = baseChoice[choice];
		//intUartSend((TIM3->CNT));
		if (calcularDistancia((TIM4->CNT)) < LeftChoice[choice]) {
			runMotor(ADELANTE, MOTOR_A);
			runMotor(ATRAS, MOTOR_B);
		} else {
			movementState = ADELANTE;
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			TIM3->CNT = 0;
			TIM4->CNT = 0;
			offset = 30;
			//intUartSend(9);
		}
		break;
	case DERECHA:
		TIM2->CCR3 = baseChoice[choice];
		TIM2->CCR4 = baseChoice[choice];
		if (calcularDistancia((TIM3->CNT)) < RightChoice[choice]) {
			runMotor(ATRAS, MOTOR_A);
			runMotor(ADELANTE, MOTOR_B);
		} else {
			movementState = ADELANTE;
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			TIM3->CNT = 0;
			TIM4->CNT = 0;
			offset = 30;
			//intUartSend(8);
		}
		break;
	case ATRAS:
		TIM2->CCR3 = baseChoice[choice];
		TIM2->CCR4 = baseChoice[choice];
		if(F == 1){
			if (calcularDistancia((TIM4->CNT)) < LeftChoice[choice] * 2) {
						runMotor(ADELANTE, MOTOR_A);
						runMotor(ATRAS, MOTOR_B);
					} else {
						movementState = ADELANTE;
						runMotor(OFF, MOTOR_A);
						runMotor(OFF, MOTOR_B);
						TIM3->CNT = 0;
						TIM4->CNT = 0;
						offset = 30;
						//intUartSend(7);
					}
		}else{
			if (calcularDistancia((TIM3->CNT)) < RightChoice[choice] * 2) {
						runMotor(ATRAS, MOTOR_A);
						runMotor(ADELANTE, MOTOR_B);
					} else {
						movementState = ADELANTE;
						runMotor(OFF, MOTOR_A);
						runMotor(OFF, MOTOR_B);
						TIM3->CNT = 0;
						TIM4->CNT = 0;
						offset = 30;
						//intUartSend(7);
					}
		}

		break;

	}
}

void CreateNode(int x, int y) {
	Map[x][y].Lados[direcciones[ADELANTE]] = lecturaSensor(ADELANTE, Sensors);
	Map[x][y].Lados[direcciones[IZQUIERDA]] = lecturaSensor(IZQUIERDA, Sensors);
	Map[x][y].Lados[direcciones[DERECHA]] = lecturaSensor(DERECHA, Sensors);
	Map[x][y].Lados[direcciones[ATRAS]] = lecturaSensor(ATRAS, Sensors);

}

void rotateAxis(int direccion) {
	switch (direccion) {
	case DERECHA:
		for (int i = 0; i < 4; i++) {
			direcciones[i] = direcciones[i] - 1;
			if (direcciones[i] == -1) {
				direcciones[i] = 3;
			}
		}
		break;
	case IZQUIERDA:
		for (int j = 0; j < 4; j++) {
			direcciones[j] = direcciones[j] + 1;
			if (direcciones[j] == 4) {
				direcciones[j] = 0;
			}
		}
		break;
	}
}

void resetAxis() {
	for (int i = 0; i < 4; i++) {
		direcciones[i] = i;
	}
}

void PrintMap() {
	for (int i = 0; i < alto; i++) {
		for (int j = 0; j < ancho; j++) {
			//SerialBT.print(Map[i][j].visitado);
			//SerialBT.print(" ");
			TX_BUFFER[0] = Map[i][j].visitado + '0';
			TX_BUFFER[1] = ' ';
			HAL_UART_Transmit(&huart1, TX_BUFFER, 2, 100);
		}
		TX_BUFFER[0] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 1, 100);
	}
}

// Called when buffer is completely filled
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	for (int i = 0; i < 10; i++) {
		CNY70[i] = adc_buf[i * 4];
		SHARP_1[i] = adc_buf[i * 4 + 1];
		SHARP_2[i] = adc_buf[i * 4 + 2];
		SHARP_3[i] = adc_buf[i * 4 + 3];
	}
	Sensors[0] = lecturaCNY70(10, CNY70);
	Sensors[1] = lecSensor(10, SHARP_1);
	Sensors[2] = lecSensor(10, SHARP_2);
	Sensors[3] = lecSensor(10, SHARP_3);

}

uint32_t MAP(uint32_t au32_IN, uint32_t au32_INmin, uint32_t au32_INmax,
		uint32_t au32_OUTmin, uint32_t au32_OUTmax) {
	return ((((au32_IN - au32_INmin) * (au32_OUTmax - au32_OUTmin))
			/ (au32_INmax - au32_INmin)) + au32_OUTmin);
}

int constrain(int x, int a, int b) {
	if (x < a) {
		return a;
	} else if (b < x) {
		return b;
	} else
		return x;
}

int wallDetector(int n, int d) {
	switch (d) {
	case ADELANTE:
		if (n < MaxCenterDistance) {
			return 1;
		} else {
			return 0;
		}
		break;

	case IZQUIERDA:
		if (n < MaxLeftDistance) {
			return 1;
		} else {
			return 0;
		}
		break;
	case DERECHA:
		if (n < MaxRightDistance) {
			return 1;
		} else {
			return 0;
		}
		break;
	default:
		return 0;
		break;
	}
}

void moveStraight() {
	if (Sensors[3] < MaxLeftDistance - 2 && Sensors[1] < MaxRightDistance - 2) {
		//intUartSend(0);
		error = Sensors[3] - Sensors[1];
	} else if (Sensors[3] < MaxLeftDistance) {
		//intUartSend(1);
		error = Sensors[3] - CenterDistanceLeft;
	} else if (Sensors[1] < MaxRightDistance) {
		//intUartSend(2);
		error = CenterDistanceRight - Sensors[1];
	} else {
		//intUartSend(3);
		error = 0;
	}

	timePrev = timeNow;
	timeNow = HAL_GetTick();
	elapsedTime = (timeNow - timePrev) / 1000;
	pidD = KD * ((error - previousError) / elapsedTime);
	pidP = KP * error;
	pid = pidP + pidD;
	if (pid > velocity) {
		//intUartSend(1);
		pid = velocity;
	}
	if (pid < -velocity) {
		//intUartSend(0);
		pid = -velocity;
	}
	//intUartSend(abs(pid));
	HAL_Delay(1);
	motLeft = velocity - pid;
	motRight = velocity + pid;
	if (motLeft < -1000) {
		motLeft = -1000;
	}
	if (motRight < -1000) {
		motRight = -1000;
	}

	previousError = error;
	motRight = constrain(motRight, -1000, 1000);
	motLeft = constrain(motLeft, -1000, 1000);

	motRight = MAP(motRight, -1000, 1000, 0, baseChoice[choice] * 2);
	motLeft = MAP(motLeft, -1000, 1000, 0, baseChoice[choice] * 2);
	TIM2->CCR4 = motLeft;
	TIM2->CCR3 = motRight;
}

void runForward() {
	runMotor(ADELANTE, MOTOR_A);
	runMotor(ADELANTE, MOTOR_B);
}

void btnMachine(int index) {
	switch (btns[index].estado) {
	case ESPERA:
		btns[index].flag = 0;
		lecturaBtn = HAL_GPIO_ReadPin(btns[index].Port, btns[index].pin);
		if (lecturaBtn == 0) {
			ticks = HAL_GetTick();
			btns[index].estado = CONFIRMACION;
		}
		break;

	case CONFIRMACION:
		lecturaBtn = HAL_GPIO_ReadPin(btns[index].Port, btns[index].pin);
		if (lecturaBtn == 0 && HAL_GetTick() >= ticks + TICKS_BTN) {
			btns[index].estado = LIBERACION;
		}

		if (lecturaBtn == 1 && ticks < TICKS_BTN) {
			btns[index].estado = ESPERA;
		}
		break;

	case LIBERACION:
		lecturaBtn = HAL_GPIO_ReadPin(btns[index].Port, btns[index].pin);
		if (lecturaBtn == 1) {
			btns[index].flag = 1;
			btns[index].estado = ESPERA;
		}
		break;
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
