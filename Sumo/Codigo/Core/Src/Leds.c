/*
 * Leds.c
 *
 *  Created on: Jul 27, 2023
 *      Author: jore
 */
#include "stm32f1xx_hal.h"
#include "main.h"

void showModeNumber(int number) {
	HAL_GPIO_WritePin(L4, number % 2);
	number /= 2;
	HAL_GPIO_WritePin(L3, number % 2);
	number /= 2;
	HAL_GPIO_WritePin(L2, number % 2);
	number /= 2;
	HAL_GPIO_WritePin(L1, number % 2);
}

