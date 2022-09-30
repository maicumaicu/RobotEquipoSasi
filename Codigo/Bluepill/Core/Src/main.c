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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sharp.h"
#include "motors.h"
#include "mpu9255.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADC_BUF_LEN 4096
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t adc_buf[ADC_BUF_LEN];
MPU9255_t MPU9255;
uint32_t CNY70[10];
uint32_t SHARP_1[10];
uint32_t SHARP_2[10];
uint32_t SHARP_3[10];
static uint32_t Sensors[4];
int direcciones[4];
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
uint8_t TX_BUFFER[1] = { 0 };
int c, m, directionsSize, movimiento;
int finishFlag, movimientoFlag;
int valueCNY;
int direcciones[4];

int mainState = SETUP;
int robotState = READING;
int movementState = OFF;
char directions[10];
Position actual;
Position last;
Node Map[alto][ancho];
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
  MX_I2C2_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	HAL_GPIO_WritePin(STBY, GPIO_PIN_SET);
	TIM4->CCR3 = 5000;
	TIM4->CCR4 = 5000;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adc_buf, ADC_BUF_LEN);
	/*while (MPU9255_Init(&hi2c2) == 1) {
	 TX_BUFFER[0] = MPU9255.yaw + '0';
	 HAL_UART_Transmit(&huart1, TX_BUFFER, sizeof(TX_BUFFER), 100);
	 }*/
	//HAL_Delay(3000);
	//HAL_UART_Receive_IT(&huart1, RX_BUFFER, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
	TIM3->CNT = 0;
	//readAll(&hi2c2, &MPU9255);
	//int yaw = MPU9255.yaw;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		//readAll(&hi2c2, &MPU9255);
		/*TX_BUFFER[0] = MPU9255.yaw + '0';
		 HAL_UART_Transmit(&huart1, TX_BUFFER, sizeof(TX_BUFFER), 100);*/
		/*if (MPU9255.yaw - yaw > 90) {
		 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
		 } else {
		 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
		 }*/
		//readAll(&hi2c2, &MPU9255);
		//MPU9255.yaw;
		//runMotor(ADELANTE, MOTOR_A);
		//runMotor(ADELANTE, MOTOR_B);
		int d = calcularDistancia(TIM3->CNT);
		TX_BUFFER[0] = TIM3->CNT;
		HAL_UART_Transmit(&huart1, TX_BUFFER, sizeof(TX_BUFFER), 100);
		if (calcularDistancia(TIM3->CNT) < 100) {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
			//HAL_Delay(100);
			//runMotor(ADELANTE, MOTOR_A);
			//runMotor(ADELANTE, MOTOR_B);
		} else {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
			//runMotor(OFF, MOTOR_A);
			//runMotor(OFF, MOTOR_B);
		}

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

void robotMachine() {
	switch (robotState) {
	case READING:
		//SerialBT.println("Rea");
		Map[actual.x][actual.y].visitado++;
		if (Map[actual.x][actual.y].visitado == 1) {
			//Serial.println("creo nodo");
			runOff(0, 0);
			CreateNode(actual.x, actual.y);
		}
		//valueCNY = lecturaCNY70(20, CNY70);

		/*if (valueCNY == BLANCO) {
		 Map[actual.x][actual.y].final = true;
		 finishFlag = 1;
		 } else {
		 Map[actual.x][actual.y].final = false;
		 robotState = CHOOSING;
		 }*/
		Map[actual.x][actual.y].final = 0;
		robotState = CHOOSING;
		//delay(1000);
		break;
	case CHOOSING:
		//SerialBT.println("Cho");
		movimiento = ChooseNextNode(actual.x, actual.y);
		movimientoFlag = 0;
		robotState = MOVING;
		break;
	case MOVING:
		movementMachine(movimiento);
		if (movimientoFlag == 1) {
			robotState = READING;
		}
		//SerialBT.println("Mov");
		break;
	}
}

int ChooseNextNode(int x, int y) {
	if (Map[x][y].Lados[direcciones[ADELANTE]] == 0) {
		Map[x][y].Lados[direcciones[ADELANTE]] = 2;
		moveNode(direcciones[ADELANTE]);
		if (Map[x][y].Lados[direcciones[ATRAS]] != 1)
			Map[x][y].Lados[direcciones[ATRAS]] = 2;
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
		}
		return ADELANTE;
	} else if (Map[x][y].Lados[direcciones[IZQUIERDA]] == 0) {
		//Serial.println("IZQUIERDA");
		//SerialBT.write('I');
		Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
		moveNode(direcciones[IZQUIERDA]);
		if (Map[x][y].Lados[direcciones[ATRAS]] != 1)
			Map[x][y].Lados[direcciones[ATRAS]] = 2;
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
		}
		rotateAxis(IZQUIERDA);
		return IZQUIERDA;
	} else if (Map[x][y].Lados[direcciones[DERECHA]] == 0) {
		//Serial.println("DERECHA");
		//SerialBT.write('D');
		Map[x][y].Lados[direcciones[DERECHA]] = 2;
		moveNode(direcciones[DERECHA]);
		if (Map[x][y].Lados[direcciones[ATRAS]] != 1)
			Map[x][y].Lados[direcciones[ATRAS]] = 2;
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
		}
		rotateAxis(DERECHA);
		return DERECHA;
	} else {
		//Serial.println("otro");
		//SerialBT.write('O');
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
		moveNode(direcciones[ADELANTE]);
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
		}
		return ADELANTE;
	} else if (Map[x][y].Lados[direcciones[IZQUIERDA]] != 1) {
		//Serial.println("IZQUIERDA1");
		Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
		moveNode(direcciones[IZQUIERDA]);
		rotateAxis(IZQUIERDA);
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
		}
		return IZQUIERDA;
	} else if (Map[x][y].Lados[direcciones[DERECHA]] != 1) {
		//Serial.println("DERECHA1");
		Map[x][y].Lados[direcciones[DERECHA]] = 2;
		moveNode(direcciones[DERECHA]);
		if (Map[x][y].visitado > 1) {
			EliminateNode(x, y);
		}
		rotateAxis(DERECHA);
		return DERECHA;
	} else if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
		//Serial.println("atras1");
		rotateAxis(DERECHA);
		rotateAxis(DERECHA);
		return ATRAS;
	}
	return 0;
}
void moveNode(int lado) {
	/*switch (lado) {
	 case ADELANTE:
	 if (visual.y != ALTO - 1) {
	 actual.y++;
	 visual.y++;
	 }
	 break;
	 case IZQUIERDA:
	 if (visual.x != 0) {
	 actual.x--;
	 visual.x--;
	 }
	 break;
	 case DERECHA:
	 if (visual.x != ANCHO - 1) {
	 actual.x++;
	 visual.x++;
	 }
	 break;
	 case ATRAS:
	 if (visual.y != 0) {
	 actual.y--;
	 visual.y--;
	 }

	 break;
	 }*/
}

void CreateNode(int x, int y) {
	/*Map[x][y].Lados[ADELANTE] = lecturaSensor(direcciones[ADELANTE], values);
	 Map[x][y].Lados[IZQUIERDA] = lecturaSensor(direcciones[IZQUIERDA], values);
	 Map[x][y].Lados[DERECHA] = lecturaSensor(direcciones[DERECHA], values);
	 Map[x][y].Lados[ATRAS] = lecturaSensor(direcciones[ATRAS], values);*/
	/*SerialBT.println(lecturaSensor(direcciones[ADELANTE]));
	 SerialBT.println(lecturaSensor(direcciones[IZQUIERDA]));
	 SerialBT.println(lecturaSensor(direcciones[DERECHA]));*/
}

/*void CreateNode(int x, int y) {
 Map[x][y].Lados[ADELANTE] = lecturaSensor(ADELANTE);
 Map[x][y].Lados[IZQUIERDA] = lecturaSensor(IZQUIERDA);
 Map[x][y].Lados[DERECHA] = lecturaSensor(DERECHA);
 Map[x][y].Lados[ATRAS] = lecturaSensor(ATRAS);
 }*/

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
	Sensors[0] = lecSensor(10, CNY70);
	Sensors[1] = lecSensor(10, SHARP_1);
	Sensors[2] = lecSensor(10, SHARP_2);
	Sensors[3] = lecSensor(10, SHARP_3);
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
