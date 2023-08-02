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
#include "HMC5883L.h"
#include "nodeControl.h"
#include "movementControl.h"
#include "velocityControl.h"
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
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
//MPU6050_t MPU6050;
uint32_t adc_buf[ADC_BUF_LEN];
uint32_t CNY70[ADC_BUF_LEN / 4];
uint32_t SHARP_1[ADC_BUF_LEN / 4];
uint32_t SHARP_2[ADC_BUF_LEN / 4];
uint32_t SHARP_3[ADC_BUF_LEN / 4];
float Sensors[4];
int direcciones[4];
uint8_t serialBuf[100];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

float KPTchoice[] = { 5, 80 }; //10 // subi este que es el de la velocidad que agarra y baja el A para que corrija mejor
float KDTchoice[] = { 1, 4 }; //0.5
float KPAchoice[] = { 7, 80 }; //17
float KDAchoice[] = { 0.5, 4 }; //0.5
float KPPchoice[] = { 2, 80, 40, 10 }; //17
float KDPchoice[] = { 0, 4, 0.5, 1, 0.5 }; //0.5
float velocityChoice[] = { 1000, 1000 };
int baseChoice[] = { 20000, 20000 }; //150
int forwardChoice[] = { 275, 290 };
int RightChoice[] = { 90, 155 };
int LeftChoice[] = { 90, 155 };
int choice;
int ticksNow;
float ppitch;
float pyaw;
float proll;
float CenterDistanceRight, CenterDistanceLeft, MaxRightDistance,
		MaxLeftDistance, MaxCenterDistance;
int calState;
int powerA;
int powerB;
int ticks, lecturaBtn;
uint8_t RX_BUFFER[1] = { 0 };
uint8_t TX_BUFFER[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int c, m, directionsSize, movimiento;
int finishFlag, movimientoFlag;
int valueCNY;
int direcciones[4];

int counter;
int tick;
button btns[CANT_BTN];
float maxDistance[3];

int q = 1;

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
float tiempoDelay;
float KPT, KDT, KPA, KDA, KPP, KDP;
float velocity;
int t, StraightFlag, xSpeed;
int objectiveDistance, direction, acelerationObjective, aceleration;

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
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
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
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	HAL_GPIO_WritePin(STBY, GPIO_PIN_SET);
	TIM4->CCR3 = 10000;
	TIM4->CCR4 = 10000;
	xSpeed = 15000;
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adc_buf, ADC_BUF_LEN);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
	TIM3->CNT = 100;
	TIM1->CNT = 100;
	offset = 25.1;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
	/*I2Cdev_init(&hi2c1);
	 HMC5883L_initialize();
	 while(HMC5883L_testConnection() == 0){

	 }*/

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		mainMachine();

		//intUartSend(calcularDistancia(TIM1->CNT)-calcularDistancia(TIM3->CNT));
		/*choice = SLOW;
		 velocity = velocityChoice[SLOW];
		 TIM2->CCR3 = baseChoice[SLOW];
		 TIM2->CCR4 = baseChoice[SLOW];
		 KPT = KPTchoice[SLOW];
		 KDT = KDTchoice[SLOW];
		 KPA = KPAchoice[SLOW];
		 KDA = KDAchoice[SLOW];
		 KPP = KPPchoice[SLOW];
		 KDP = KDPchoice[SLOW];*/
		//moveStraight();
		//movementMachine(ADELANTE);
		/*if(ticksNow + 100 < HAL_GetTick()){
		 intUartSend(HMC5883L_getHeadingZ());
		 ticksNow = HAL_GetTick();
		 }*/
		//intUartSend(TIM1->CNT);
		/*runMotor(ADELANTE, MOTOR_A);
		 runMotor(ADELANTE, MOTOR_B);*/
		btnMachine(0);
		btnMachine(1);
		btnMachine(2);
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

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 4;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 10;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 10;
  if (HAL_TIM_Encoder_Init(&htim1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 10;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_Pin|STBY_Pin|AIN1_Pin|AIN2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, BIN2_Pin|BIN1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN1_Pin BTN2_Pin BTN3_Pin */
  GPIO_InitStruct.Pin = BTN1_Pin|BTN2_Pin|BTN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Pin STBY_Pin AIN1_Pin AIN2_Pin */
  GPIO_InitStruct.Pin = LED_Pin|STBY_Pin|AIN1_Pin|AIN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BIN2_Pin BIN1_Pin */
  GPIO_InitStruct.Pin = BIN2_Pin|BIN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void intUartSend(float entero) {

	int m;
	int c;
	int d;
	int u;
	int de1;
	int de2;

	m = abs(entero / 1000);
	c = abs(entero / 100) - m * 10;
	d = abs(entero / 10) - (m * 100 + c * 10);
	u = abs(entero) - (m * 1000 + c * 100 + d * 10);
	if (entero > 0) {
		de1 = (entero - (m * 1000 + c * 100 + d * 10 + u)) * 10;
		de2 = (entero - (m * 1000 + c * 100 + d * 10 + u + de1 * 0.1)) * 100;
		TX_BUFFER[0] = m + '0';
		TX_BUFFER[1] = c + '0';
		TX_BUFFER[2] = d + '0';
		TX_BUFFER[3] = u + '0';
		TX_BUFFER[4] = ',';
		TX_BUFFER[5] = de1 + '0';
		TX_BUFFER[6] = de2 + '0';
		TX_BUFFER[7] = '\n';
		HAL_UART_Transmit(&huart3, TX_BUFFER, 8, 100);
	} else {
		de1 = ((-(entero)) - (m * 1000 + c * 100 + d * 10 + u)) * 10;
		de2 = ((-(entero)) - (m * 1000 + c * 100 + d * 10 + u + de1 * 0.1))
				* 100;
		TX_BUFFER[0] = '-';
		TX_BUFFER[1] = m + '0';
		TX_BUFFER[2] = c + '0';
		TX_BUFFER[3] = d + '0';
		TX_BUFFER[4] = u + '0';
		TX_BUFFER[5] = ',';
		TX_BUFFER[6] = de1 + '0';
		TX_BUFFER[7] = de2 + '0';
		TX_BUFFER[8] = '\n';
		HAL_UART_Transmit(&huart3, TX_BUFFER, 9, 100);
	}

	/*TX_BUFFER[0] = m + '0';
	 TX_BUFFER[1] = c + '0';
	 TX_BUFFER[2] = d + '0';
	 TX_BUFFER[3] = u + '0';
	 TX_BUFFER[4] = ',';
	 TX_BUFFER[5] = de1 + '0';
	 TX_BUFFER[6] = de2 + '0';
	 TX_BUFFER[7] = '\n';
	 HAL_UART_Transmit(&huart3, TX_BUFFER, 8, 100);*/
}

void mainMachine() {
	switch (mainState) {
	case SETUP:
		actual.x = ALTO;
		actual.y = ANCHO;
		/*visual.x = 0;
		 visual.y = 0;*/
		resetAxis(direcciones);
		movimientoFlag = 0;
		finishFlag = 0;
		/*if (Sensors[1] - Sensors[3] < 0.5 && Sensors[1] - Sensors[3] > -0.5) {
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
		 } else {
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		 }*/
		if (btns[0].flag == 1) {
			// Set The LED ON!
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
			choice = SLOW;
			velocity = velocityChoice[SLOW];
			TIM2->CCR3 = baseChoice[SLOW];
			TIM2->CCR4 = baseChoice[SLOW];
			KPT = KPTchoice[SLOW];
			KDT = KDTchoice[SLOW];
			KPA = KPAchoice[SLOW];
			KDA = KDAchoice[SLOW];
			KPP = KPPchoice[SLOW];
			KDP = KDPchoice[SLOW];
			if (t == 0) {
				mainState = CALIBRATE;
				t++;
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
			KPT = KPTchoice[FAST];
			KDT = KDTchoice[FAST];
			KPA = KPAchoice[FAST];
			KDA = KDAchoice[FAST];
			KPP = KPPchoice[FAST];
			KDP = KDPchoice[FAST];
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
			KPT = KPTchoice[FAST];
			KDT = KDTchoice[FAST];
			KPA = KPAchoice[FAST];
			KDA = KDAchoice[FAST];
			KPP = KPPchoice[FAST];
			KDP = KDPchoice[FAST];
			if (t == 0) {
				mainState = CALIBRATE;
				t++;
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
			HAL_UART_Transmit(&huart3, TX_BUFFER, 1, 100);
			intUartSend(actual.x);
			TX_BUFFER[0] = 'Y';
			HAL_UART_Transmit(&huart3, TX_BUFFER, 1, 100);
			intUartSend(actual.y);
			actual.x = ALTO;
			actual.y = ANCHO;
			//visual.x = 0;
			//visual.y = 0;
			finishFlag = 0;
			resetAxis(direcciones);
			PrintMap();
			mainState = RESOLUTION;
		}
		break;
	case RESOLUTION:
		if (Map[actual.x][actual.y].final == 0) {
			addDirection(actual.x, actual.y);
			TX_BUFFER[0] = 'X';
			HAL_UART_Transmit(&huart3, TX_BUFFER, 1, 100);
			intUartSend(actual.x);
			TX_BUFFER[0] = 'Y';
			HAL_UART_Transmit(&huart3, TX_BUFFER, 1, 100);
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
		intUartSend(Sensors[1] - Sensors[3]);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		if (Sensors[1] - Sensors[3] < 0.5 && Sensors[1] - Sensors[3] > -0.5) {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			if (btns[0].flag == 1) {
				CenterDistanceRight = Sensors[3];
				CenterDistanceLeft = Sensors[1];
				calState = LEFT;
			}
		}
		/*runMotor(ADELANTE, MOTOR_A);
		 runMotor(ADELANTE, MOTOR_B);
		 StraightFlag = 1;*/
		break;
	case LEFT:
		intUartSend((Sensors[3]));
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		if (btns[0].flag == 1) {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			maxDistance[1] = Sensors[3] + 2;
			calState = RIGHT;
		}
		break;
	case RIGHT:
		intUartSend((Sensors[1]));
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		if (btns[0].flag == 1) {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			maxDistance[2] = Sensors[1] + 2;
			calState = FORWARD;
		}
		break;
	case FORWARD:
		intUartSend((Sensors[2]));
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		if (btns[0].flag == 1) {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			maxDistance[0] = Sensors[2];
			mainState = SETUP;
			calState = CENTER;
		}
		break;
	}
}

void robotMachine() {
	switch (robotState) {
	case READING:
		//HAL_Delay(10);
		TX_BUFFER[0] = 'X';
		TX_BUFFER[1] = actual.x + '0';
		TX_BUFFER[2] = '\n';
		TX_BUFFER[3] = 'Y';
		TX_BUFFER[4] = actual.y + '0';
		TX_BUFFER[5] = '\n';
		HAL_UART_Transmit(&huart3, TX_BUFFER, 6, 100);
		Map[actual.x][actual.y].visitado++;

		if (Map[actual.x][actual.y].visitado == 1) {
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			CreateNode(&Map[actual.x][actual.y], Sensors, direcciones,
					maxDistance);
			if (q == 1) {
				Map[actual.x][actual.y].Lados[direcciones[ATRAS]] = 1;
				q = 0;
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
		valueCNY = NEGRO;			//Sensors[0];
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
		HAL_UART_Transmit(&huart3, TX_BUFFER, 3, 100);

		TX_BUFFER[0] = '*';
		TX_BUFFER[1] = '*';
		TX_BUFFER[2] = '\n';
		HAL_UART_Transmit(&huart3, TX_BUFFER, 3, 100);
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
			//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
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
	HAL_UART_Transmit(&huart3, TX_BUFFER, 1, 100);
	if (movimientoFlag == 1) {
		m++;
		movimientoFlag = 0;
	}
}

void addDirection(int x, int y) {
	if (Map[x][y].Lados[direcciones[ADELANTE]] != 1) {
		//Map[x][y].Lados[direcciones[ADELANTE]] = 2;
		moveNode(direcciones[ADELANTE], &actual);
		directions[directionsSize] = 'a';
	} else if (Map[x][y].Lados[direcciones[IZQUIERDA]] != 1) {
		//Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
		moveNode(direcciones[IZQUIERDA], &actual);
		rotateAxis(IZQUIERDA, direcciones);
		directions[directionsSize] = 'i';
	} else if (Map[x][y].Lados[direcciones[DERECHA]] != 1) {
		//Map[x][y].Lados[direcciones[DERECHA]] = 2;
		moveNode(direcciones[DERECHA], &actual);
		rotateAxis(DERECHA, direcciones);
		directions[directionsSize] = 'd';
	}
	intUartSend(Map[x][y].Lados[direcciones[ADELANTE]]);
	intUartSend(Map[x][y].Lados[direcciones[IZQUIERDA]]);
	intUartSend(Map[x][y].Lados[direcciones[DERECHA]]);
	TX_BUFFER[0] = 'D';
	TX_BUFFER[1] = directions[directionsSize];
	TX_BUFFER[2] = '\n';
	HAL_UART_Transmit(&huart3, TX_BUFFER, 3, 100);
	directionsSize++;
}

int ChooseNextNode(int x, int y) {
	if (Map[x][y].Lados[direcciones[ADELANTE]] == 0) {
		TX_BUFFER[0] = 'A';
		TX_BUFFER[1] = '\n';
		HAL_UART_Transmit(&huart3, TX_BUFFER, 2, 100);
		Map[x][y].Lados[direcciones[ADELANTE]] = 2;
		/*if (Map[x][y].visitado > 1) {
		 EliminateNode(&Map[actual.x][actual.y], &Map[last.x][last.y],
		 direcciones[ATRAS]);
		 intUartSend(5000);
		 }*/
		if (Map[x][y].Lados[direcciones[ATRAS]] != 1)
			Map[x][y].Lados[direcciones[ATRAS]] = 2;
		last.x = actual.x;
		last.y = actual.y;
		intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);
		moveNode(direcciones[ADELANTE], &actual);
		return ADELANTE;
	} else if (Map[x][y].Lados[direcciones[IZQUIERDA]] == 0) {
		TX_BUFFER[0] = 'I';
		TX_BUFFER[1] = '\n';
		HAL_UART_Transmit(&huart3, TX_BUFFER, 2, 100);
		Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
		/*if (Map[x][y].visitado > 1) {
		 EliminateNode(&Map[actual.x][actual.y], &Map[last.x][last.y],
		 direcciones[ATRAS]);
		 intUartSend(5000);
		 }*/
		/*if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
		 Map[x][y].Lados[direcciones[ATRAS]] = 2;
		 }*/
		last.x = actual.x;
		last.y = actual.y;
		intUartSend(Map[x][y].Lados[DERECHA]);
		intUartSend(Map[x][y].Lados[ADELANTE]);
		intUartSend(Map[x][y].Lados[IZQUIERDA]);
		intUartSend(Map[x][y].Lados[ATRAS]);
		moveNode(direcciones[IZQUIERDA], &actual);
		rotateAxis(IZQUIERDA, direcciones);
		return IZQUIERDA;
	} else if (Map[x][y].Lados[direcciones[DERECHA]] == 0) {
		TX_BUFFER[0] = 'D';
		TX_BUFFER[1] = '\n';
		HAL_UART_Transmit(&huart3, TX_BUFFER, 2, 100);

		/*if (Map[x][y].visitado > 1) {
		 EliminateNode(&Map[actual.x][actual.y], &Map[last.x][last.y],
		 direcciones[ATRAS]);
		 intUartSend(5000);
		 }*/
		Map[x][y].Lados[direcciones[DERECHA]] = 2;
		/*if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
		 intUartSend(Map[x][y].Lados[direcciones[ATRAS]]);
		 Map[x][y].Lados[direcciones[ATRAS]] = 2;
		 }*/
		last.x = actual.x;
		last.y = actual.y;
		intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);
		moveNode(direcciones[DERECHA], &actual);
		rotateAxis(DERECHA, direcciones);
		return DERECHA;
	} else {
		TX_BUFFER[0] = 'O';
		TX_BUFFER[1] = '\n';
		HAL_UART_Transmit(&huart3, TX_BUFFER, 2, 100);
		return SearchAvailableNode(x, y);
	}

}

int SearchAvailableNode(int x, int y) {
	if (Map[x][y].Lados[direcciones[ADELANTE]] != 1) {
		//Serial.println("Adelante1");

		/*if (Map[x][y].visitado > 1) {
		 EliminateNode(&Map[actual.x][actual.y], &Map[last.x][last.y],
		 direcciones[ATRAS]);
		 intUartSend(4000);
		 }*/
		last.x = actual.x;
		last.y = actual.y;
		intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);
		moveNode(direcciones[ADELANTE], &actual);

		return ADELANTE;
	} else if (Map[x][y].Lados[direcciones[IZQUIERDA]] != 1) {
		//Serial.println("IZQUIERDA1");l
		//moveNode(IZQUIERDA);
		//rotateAxis(IZQUIERDA);
		/*if (Map[x][y].visitado > 1) {
		 EliminateNode(&Map[actual.x][actual.y], &Map[last.x][last.y],
		 direcciones[ATRAS]);
		 intUartSend(4000);
		 }*/
		last.x = actual.x;
		last.y = actual.y;
		intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);
		moveNode(direcciones[IZQUIERDA], &actual);

		rotateAxis(IZQUIERDA, direcciones);
		return IZQUIERDA;
	} else if (Map[x][y].Lados[direcciones[DERECHA]] != 1) {
		//Serial.println("DERECHA1");
		/*if (Map[x][y].visitado > 1) {
		 EliminateNode(&Map[actual.x][actual.y], &Map[last.x][last.y],
		 direcciones[ATRAS]);
		 intUartSend(4000);
		 }*/
		last.x = actual.x;
		last.y = actual.y;
		intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);
		moveNode(direcciones[DERECHA], &actual);
		rotateAxis(DERECHA, direcciones);
		return DERECHA;
	} else if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
		last.x = actual.x;
		last.y = actual.y;
		intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
		intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
		intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
		intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);
		//Map[x][y].Lados[direcciones[ATRAS]] = 2;
		moveNode(direcciones[ATRAS], &actual);

		rotateAxis(DERECHA, direcciones);
		rotateAxis(DERECHA, direcciones);
		return ATRAS;
	}
	return 0;
}
/*void moveNode(int lado) {
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
 }*/

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
/*void movementMachine(int move) {
 switch (movementState) {
 case OFF:
 runMotor(OFF, MOTOR_A);
 runMotor(OFF, MOTOR_B);
 if (move != OFF) {
 movementState = move;
 if (move != ADELANTE) {
 TIM3->CNT = 0;
 TIM1->CNT = 0;
 }
 //intUartSend(TIM3->CNT);
 }
 break;
 case ADELANTE:
 //TIM4->CCR3 = xSpeed;
 //TIM4->CCR4 = xSpeed;
 //intUartSend(calcularDistancia((TIM1->CNT)));
 intUartSend(TIM3->CNT);
 if ((calcularDistancia((TIM3->CNT)) < forwardChoice[choice] / 5 + offset)
 || (calcularDistancia((TIM1->CNT))
 < forwardChoice[choice] / 5 + offset) && Sensors[2] > 5) {
 //moveStraight();
 StraightFlag = 1;
 intUartSend(1);
 xSpeed = (calcularDistancia(TIM3->CNT) - offset)
 * (((baseChoice[choice]) - ((baseChoice[choice]) / 3))
 / (forwardChoice[choice] / 5))
 + (baseChoice[choice]) / 3;
 runMotor(ADELANTE, MOTOR_A);
 runMotor(ADELANTE, MOTOR_B);
 } else if ((calcularDistancia((TIM3->CNT))
 < forwardChoice[choice] * (4 / 5) + offset)
 || (calcularDistancia((TIM1->CNT))
 < forwardChoice[choice] * (4 / 5) + offset)) {
 xSpeed = baseChoice[choice];
 runMotor(ADELANTE, MOTOR_A);
 runMotor(ADELANTE, MOTOR_B);
 intUartSend(2);
 } else if ((calcularDistancia((TIM3->CNT))
 < forwardChoice[choice] + offset)
 || (calcularDistancia((TIM1->CNT))
 < forwardChoice[choice] + offset)) {
 xSpeed = baseChoice[choice]
 - ((calcularDistancia((TIM1->CNT)) - offset)
 * (baseChoice[choice] / forwardChoice[choice])
 - baseChoice[choice] / 1.8);
 runMotor(ADELANTE, MOTOR_A);
 runMotor(ADELANTE, MOTOR_B);
 intUartSend(3);
 } else {
 StraightFlag = 0;
 movimientoFlag = 1;
 movementState = OFF;
 runMotor(OFF, MOTOR_A);
 runMotor(OFF, MOTOR_B);
 //TIM3->CNT = 0;
 //TIM1->CNT = 0;
 offset = calcularDistancia((TIM3->CNT));
 //intUartSend(10);
 }
 break;
 case IZQUIERDA:
 TIM4->CCR3 = baseChoice[choice]
 - (calcularDistancia((TIM3->CNT))
 * (baseChoice[choice] / LeftChoice[choice])
 - baseChoice[choice] / 1.8);
 TIM4->CCR4 = baseChoice[choice]
 - (calcularDistancia((TIM3->CNT))
 * (baseChoice[choice] / LeftChoice[choice])
 - baseChoice[choice] / 1.8);
 //intUartSend((TIM3->CNT));
 if (calcularDistancia((TIM3->CNT)) < LeftChoice[choice]) {
 runMotor(ADELANTE, MOTOR_A);
 runMotor(ATRAS, MOTOR_B);
 } else {
 movementState = ADELANTE;
 runMotor(OFF, MOTOR_A);
 runMotor(OFF, MOTOR_B);
 TIM3->CNT = 0;
 TIM1->CNT = 0;
 offset = 0;
 //intUartSend(9);
 }
 break;
 case DERECHA:
 TIM4->CCR3 = baseChoice[choice]
 - (calcularDistancia((TIM1->CNT))
 * (baseChoice[choice] / RightChoice[choice])
 - baseChoice[choice] / 1.8);
 TIM4->CCR4 = baseChoice[choice]
 - (calcularDistancia((TIM1->CNT))
 * (baseChoice[choice] / RightChoice[choice])
 - baseChoice[choice] / 1.8);
 if (calcularDistancia((TIM1->CNT)) < RightChoice[choice]) {
 runMotor(ATRAS, MOTOR_A);
 runMotor(ADELANTE, MOTOR_B);
 //intUartSend("HOLA");
 } else {
 movementState = ADELANTE;
 runMotor(OFF, MOTOR_A);
 runMotor(OFF, MOTOR_B);
 TIM3->CNT = 0;
 TIM1->CNT = 0;
 offset = 0;
 //intUartSend(8);
 }
 break;
 case ATRAS:
 TIM4->CCR3 = baseChoice[choice];
 TIM4->CCR4 = baseChoice[choice];
 if (calcularDistancia((TIM1->CNT)) < RightChoice[choice] * 2) {
 runMotor(ATRAS, MOTOR_A);
 runMotor(ADELANTE, MOTOR_B);
 } else {
 movementState = ADELANTE;
 runMotor(OFF, MOTOR_A);
 runMotor(OFF, MOTOR_B);
 TIM3->CNT = 0;
 TIM1->CNT = 0;
 offset = 0;
 //intUartSend(7);
 }
 break;

 }
 }*/

/*void CreateNode(int x, int y) {
 Map[x][y].Lados[direcciones[ADELANTE]] = lecturaSensor(ADELANTE, Sensors, maxDistance);
 Map[x][y].Lados[direcciones[IZQUIERDA]] = lecturaSensor(IZQUIERDA, Sensors, maxDistance);
 Map[x][y].Lados[direcciones[DERECHA]] = lecturaSensor(DERECHA, Sensors, maxDistance);
 Map[x][y].Lados[direcciones[ATRAS]] = lecturaSensor(ATRAS, Sensors, maxDistance);
 */

/*void rotateAxis(int direccion) {
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
 }*/

void PrintMap() {
	for (int i = 0; i < alto; i++) {
		for (int j = 0; j < ancho; j++) {
			//SerialBT.print(Map[i][j].visitado);
			//SerialBT.print(" ");
			TX_BUFFER[0] = Map[i][j].visitado + '0';
			TX_BUFFER[1] = ' ';
			HAL_UART_Transmit(&huart3, TX_BUFFER, 2, 100);
		}
		TX_BUFFER[0] = '\n';
		HAL_UART_Transmit(&huart3, TX_BUFFER, 1, 100);
	}
}

// Called when buffer is completely filled
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	for (int i = 0; i < 100; i++) {
		CNY70[i] = adc_buf[i * 4];
		SHARP_1[i] = adc_buf[i * 4 + 1];
		SHARP_2[i] = adc_buf[i * 4 + 2];
		SHARP_3[i] = adc_buf[i * 4 + 3];
	}
	Sensors[0] = lecturaCNY70(100, CNY70);
	Sensors[1] = lecSensor(100, SHARP_1);
	Sensors[2] = lecSensor(100, SHARP_2);
	Sensors[3] = lecSensor(100, SHARP_3);

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
