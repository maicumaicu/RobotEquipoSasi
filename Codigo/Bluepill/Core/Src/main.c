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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADC_BUF_LEN 1024
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
static uint32_t Sensors[4];
int direcciones[4];
uint8_t serialBuf[100];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int powerA;
int powerB;
uint8_t RX_BUFFER[1] = { 0 };
uint8_t TX_BUFFER[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
float KP, KD, tiempoDelay;
float velocity;
float KPchoice[2] = { 100, 100 }; //17                           //Elección de constante proporcional del PID
float KDchoice[2] = { 10, 500 }; //0.5                          //Elección de constante derivada del PID
float velocityChoice[2] = { 80, 800 }; //150
int c, m, directionsSize, movimiento;
int finishFlag, movimientoFlag;
int valueCNY;
int direcciones[4];
int offset;
int counter;

int mainState = SETUP;
int robotState = READING;
int movementState = OFF;
char directions[10];
Position actual;
Position last;
Node Map[alto][ancho];
float error, pid, previousError, elapsedTime, timeNow, timePrev, pidP, pidD;
int motLeft, motRight;
/*Position visual;
 Node VisualMap[ALTO][ANCHO];*/
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

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
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

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
		if (!HAL_GPIO_ReadPin(BTN1)) {
			// Set The LED ON!
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
			TX_BUFFER[0] = 'S';
			HAL_UART_Transmit(&huart1, TX_BUFFER, sizeof(TX_BUFFER), 100);
			velocity = velocityChoice[SLOW];
			TIM2->CCR3 = 8000;
			TIM2->CCR4 = 8000;
			KP = KPchoice[SLOW];
			KD = KDchoice[SLOW];
			mainState = MAPPING;
		}
		if (!HAL_GPIO_ReadPin(BTN2)) {
			// Set The LED ON!
			mainState = RACING;
			//directions = ReadRun();
			//ShowRun();
		}
		//confirmacionCentrado();
		break;
	case MAPPING:
		if (finishFlag == 0) {
			robotMachine();
			/*TX_BUFFER[0] = 'L';
			 HAL_UART_Transmit(&huart1, TX_BUFFER, sizeof(TX_BUFFER), 100);*/
		} else {
			actual.x = ALTO;
			actual.y = ANCHO;
			//visual.x = 0;
			//visual.y = 0;
			finishFlag = 0;
			resetAxis();
			//PrintMap();
			mainState = RESOLUTION;
		}
		break;
		/*case RESOLUTION:
		 if (Map[actual.x][actual.y].final == false) {
		 addDirection(actual.x, actual.y);
		 } else {

		 directions = optimizeDirections(directions);
		 SerialBT.println(directions);
		 UploadRun(directions);
		 mainState = SETUP;
		 }

		 break;
		 case RACING:
		 //runDirections(directions);
		 break;
		 }*/

	}
}

void robotMachine() {
	switch (robotState) {
	case READING:
		Map[actual.x][actual.y].visitado++;
		if (Map[actual.x][actual.y].visitado == 1) {
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			CreateNode(actual.x, actual.y);
			TX_BUFFER[0] = 'D';
			TX_BUFFER[1] = Sensors[1] + '0';
			TX_BUFFER[2] = '\n';
			TX_BUFFER[3] = 'C';
			TX_BUFFER[4] = Sensors[2] + '0';
			TX_BUFFER[5] = '\n';
			TX_BUFFER[6] = 'I';
			TX_BUFFER[7] = Sensors[3] + '0';
			TX_BUFFER[8] = '\n';
			HAL_UART_Transmit(&huart1, TX_BUFFER, 9, 100);
			TX_BUFFER[0] = 'D';
			TX_BUFFER[1] = direcciones[DERECHA] + '0';
			TX_BUFFER[2] = '\n';
			TX_BUFFER[3] = 'C';
			TX_BUFFER[4] = direcciones[ADELANTE] + '0';
			TX_BUFFER[5] = '\n';
			TX_BUFFER[6] = 'I';
			TX_BUFFER[7] = direcciones[IZQUIERDA] + '0';
			TX_BUFFER[8] = '\n';
			TX_BUFFER[9] = 'A';
			TX_BUFFER[10] = direcciones[ATRAS] + '0';
			TX_BUFFER[11] = '\n';
			HAL_UART_Transmit(&huart1, TX_BUFFER, 12, 100);
		}
		TX_BUFFER[0] = 'D';
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
		valueCNY = NEGRO;
		if (valueCNY == BLANCO) {
			Map[actual.x][actual.y].final = 1;
			finishFlag = 1;
		} else {
			Map[actual.x][actual.y].final = 0;
			robotState = CHOOSING;
		}
		HAL_Delay(1000);
		break;
	case CHOOSING:
		movimiento = ChooseNextNode(actual.x, actual.y);
		TX_BUFFER[0] = 'M';
		TX_BUFFER[1] = movimiento + '0';
		TX_BUFFER[2] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 3, 100);
		if (movimiento == IZQUIERDA) {
			rotateAxis(IZQUIERDA);
			if (Map[actual.x][actual.y].Lados[direcciones[ATRAS]] != 1)
				Map[actual.x][actual.y].Lados[direcciones[ATRAS]] = 2;
			moveNode(IZQUIERDA);
			counter--;
		} else if (movimiento == DERECHA) {
			rotateAxis(DERECHA);
			if (Map[actual.x][actual.y].Lados[direcciones[ATRAS]] != 1)
				Map[actual.x][actual.y].Lados[direcciones[ATRAS]] = 2;
			moveNode(DERECHA);
			counter++;
		} else if (movimiento == ATRAS) {
			counter++;
			counter++;
			rotateAxis(DERECHA);
			rotateAxis(DERECHA);
			if (Map[actual.x][actual.y].Lados[direcciones[ATRAS]] != 1)
				Map[actual.x][actual.y].Lados[direcciones[ATRAS]] = 2;
			moveNode(ATRAS);

		}

		TX_BUFFER[0] = '*';
		TX_BUFFER[1] = '*';
		TX_BUFFER[2] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 3, 100);
		movimientoFlag = 0;
		robotState = MOVING;

		break;
	case MOVING:
		//TX_BUFFER[0] = 'M';
		//HAL_UART_Transmit(&huart1, TX_BUFFER, sizeof(TX_BUFFER), 100);
		movementMachine(movimiento);
		if (movimientoFlag == 1) {
			robotState = READING;
		}
		break;
	}
}

int ChooseNextNode(int x, int y) {
	if (Map[x][y].Lados[direcciones[ADELANTE]] == 0) {
		TX_BUFFER[0] = 'A';
		TX_BUFFER[1] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 2, 100);
		Map[x][y].Lados[direcciones[ADELANTE]] = 2;
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
		}
		moveNode(ADELANTE);
		if (Map[x][y].Lados[direcciones[ATRAS]] != 1)
			Map[x][y].Lados[direcciones[ATRAS]] = 2;
		TX_BUFFER[0] = 'D';
		TX_BUFFER[1] = Map[x][y].Lados[DERECHA] + '0';
		TX_BUFFER[2] = '\n';
		TX_BUFFER[3] = 'C';
		TX_BUFFER[4] = Map[x][y].Lados[ADELANTE] + '0';
		TX_BUFFER[5] = '\n';
		TX_BUFFER[6] = 'I';
		TX_BUFFER[7] = Map[x][y].Lados[IZQUIERDA] + '0';
		TX_BUFFER[8] = '\n';
		TX_BUFFER[9] = 'A';
		TX_BUFFER[10] = Map[x][y].Lados[ATRAS] + '0';
		TX_BUFFER[11] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 12, 100);

		return ADELANTE;
	} else if (Map[x][y].Lados[direcciones[IZQUIERDA]] == 0) {
		TX_BUFFER[0] = 'I';
		TX_BUFFER[1] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 2, 100);
		Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;

		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
		}
		TX_BUFFER[0] = 'D';
		TX_BUFFER[1] = Map[x][y].Lados[DERECHA] + '0';
		TX_BUFFER[2] = '\n';
		TX_BUFFER[3] = 'C';
		TX_BUFFER[4] = Map[x][y].Lados[ADELANTE] + '0';
		TX_BUFFER[5] = '\n';
		TX_BUFFER[6] = 'I';
		TX_BUFFER[7] = Map[x][y].Lados[IZQUIERDA] + '0';
		TX_BUFFER[8] = '\n';
		TX_BUFFER[9] = 'A';
		TX_BUFFER[10] = Map[x][y].Lados[ATRAS] + '0';
		TX_BUFFER[11] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 12, 100);

		return IZQUIERDA;
	} else if (Map[x][y].Lados[direcciones[DERECHA]] == 0) {
		TX_BUFFER[0] = 'D';
		TX_BUFFER[1] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 2, 100);
		Map[x][y].Lados[direcciones[DERECHA]] = 2;
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
		}
		TX_BUFFER[0] = 'D';
		TX_BUFFER[1] = Map[x][y].Lados[DERECHA] + '0';
		TX_BUFFER[2] = '\n';
		TX_BUFFER[3] = 'C';
		TX_BUFFER[4] = Map[x][y].Lados[ADELANTE] + '0';
		TX_BUFFER[5] = '\n';
		TX_BUFFER[6] = 'I';
		TX_BUFFER[7] = Map[x][y].Lados[IZQUIERDA] + '0';
		TX_BUFFER[8] = '\n';
		TX_BUFFER[9] = 'A';
		TX_BUFFER[10] = Map[x][y].Lados[ATRAS] + '0';
		TX_BUFFER[11] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 12, 100);

		return DERECHA;
	} else {
		TX_BUFFER[0] = 'O';
		TX_BUFFER[1] = '\n';
		HAL_UART_Transmit(&huart1, TX_BUFFER, 2, 100);
		return SearchAvailableNode(x, y);
	}
	last.x = x;
	last.y = y;
}

void EliminateNode(int x, int y) {
//Serial.println("Borro");
	Map[x][y].Lados[direcciones[ATRAS]] = 1;
	Map[last.x][last.y].visitado = 0;
}

int SearchAvailableNode(int x, int y) {
	if (Map[x][y].Lados[direcciones[ADELANTE]] != 1) {
		//Serial.println("Adelante1");
		Map[x][y].Lados[direcciones[ADELANTE]] = 2;
		moveNode(ADELANTE);
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
		}
		return ADELANTE;
	} else if (Map[x][y].Lados[direcciones[IZQUIERDA]] != 1) {
		//Serial.println("IZQUIERDA1");
		Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
		moveNode(IZQUIERDA);
		//rotateAxis(IZQUIERDA);
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
		}
		return IZQUIERDA;
	} else if (Map[x][y].Lados[direcciones[DERECHA]] != 1) {
		//Serial.println("DERECHA1");
		Map[x][y].Lados[direcciones[DERECHA]] = 2;
		moveNode(DERECHA);
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
		}
		//rotateAxis(DERECHA);
		return DERECHA;
	} else if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
		//Serial.println("atras1");
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
void movementMachine(int move) {
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

		if (calcularDistancia((TIM3->CNT) >> 1) < FORWARD_DISTANCE - offset
				|| calcularDistancia((TIM4->CNT) >> 1)
						< FORWARD_DISTANCE - offset) {
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

		if (calcularDistancia(TIM3->CNT) < 155) {
			runMotor(ATRAS, MOTOR_A);
			runMotor(ADELANTE, MOTOR_B);
		} else {
			movementState = ADELANTE;
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			TIM3->CNT = 0;
			TIM4->CNT = 0;
			offset = 20;
		}
		break;
	case DERECHA:
		if (calcularDistancia(TIM4->CNT) < 155) {
			runMotor(ADELANTE, MOTOR_A);
			runMotor(ATRAS, MOTOR_B);
		} else {
			movementState = ADELANTE;
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			TIM3->CNT = 0;
			TIM4->CNT = 0;
			offset = 20;
		}
		break;
	case ATRAS:
		if (calcularDistancia(TIM4->CNT) < 290) {
			runMotor(ADELANTE, MOTOR_A);
			runMotor(ATRAS, MOTOR_B);
		} else {
			movementState = ADELANTE;
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			TIM3->CNT = 0;
			TIM4->CNT = 0;
			offset = 20;
		}
		break;
		/*case SUPER:
		 int X = directions[m] - '0';
		 if (calcularDistancia(counterD) < FORWARD_DISTANCE * X
		 && calcularDistancia(counterI) < FORWARD_DISTANCE * X) {
		 estabilizacion();
		 powerA = 200;
		 powerB = 200;
		 runForward(powerA, powerB);
		 } else {
		 movimientoFlag = 1;
		 movementState = OFF;
		 }
		 break;*/
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
		}
		//SerialBT.println();
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

void moveStraight() {
	error = Sensors[3] - 9;

	timePrev = timeNow;
	timeNow = HAL_GetTick();
	elapsedTime = (timeNow - timePrev) / 1000;
	pidD = KD * ((error - previousError) / elapsedTime);
	pidP = KP * error;
	pid = pidP + pidD;
	if (pid > velocity) {
		pid = velocity;
	}
	if (pid < -velocity) {
		pid = -velocity;
	}

	motRight = velocity - pid;
	motLeft = velocity + pid;
	if (motLeft < 0) {
		motLeft = 0;
	}
	if (motRight < 0) {
		motRight = 0;
	}

	//setMotors(motLeft, motRight);
	previousError = error;
	motRight = constrain(motRight, -1000, 1000);
	motLeft = constrain(motLeft, -1000, 1000);
	motRight = MAP(motRight, -1000, 1000, 0, 15000);
	motLeft = MAP(motLeft, -1000, 1000, 0, 15000);
	TIM2->CCR3 = motRight;
	TIM2->CCR4 = motLeft;
}

void runForward() {
	runMotor(ADELANTE, MOTOR_A);
	runMotor(ADELANTE, MOTOR_B);
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
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
