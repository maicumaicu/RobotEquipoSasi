/*
 * UsefulFunctions.c
 *
 *  Created on: Jul 25, 2023
 *      Author: jore
 */
#include "UsefulFunctions.h"
#include "stm32f1xx_hal.h"
#include "main.h"
int ticks = 0;
int lecturaBtn = 0;

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


void btnMachine(button* btn) {
	switch (btn->estado) {
	case ESPERA:
		(*btn).flag = 0;
		lecturaBtn = HAL_GPIO_ReadPin((*btn).PIN.Port, (*btn).PIN.pin);
		if (lecturaBtn == 0) {

			ticks = HAL_GetTick();
			(*btn).estado = CONFIRMACION;
		}
		break;

	case CONFIRMACION:
		lecturaBtn = HAL_GPIO_ReadPin((*btn).PIN.Port, (*btn).PIN.pin);
		if (lecturaBtn == 0 && HAL_GetTick() >= ticks + TICKS_BTN) {

			(*btn).estado = LIBERACION;
		}

		if (lecturaBtn == 1 && ticks < TICKS_BTN) {

			(*btn).estado = ESPERA;
		}
		break;

	case LIBERACION:
		lecturaBtn = HAL_GPIO_ReadPin((*btn).PIN.Port, (*btn).PIN.pin);
		if (lecturaBtn == 1) {
			(*btn).flag = 1;
			(*btn).estado = ESPERA;
		}
		break;
	}
}


