/*
 * motors.c
 *
 *  Created on: Jul 24, 2023
 *      Author: jore
 */

#include "motors.h"
void runMotor(int dir, motor motor) {
	switch (dir) {
	case ADELANTE:
		HAL_GPIO_WritePin(motor.IN1.Port,motor.IN1.pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(motor.IN2.Port,motor.IN2.pin, GPIO_PIN_RESET);
		break;
	case ATRAS:
		HAL_GPIO_WritePin(motor.IN1.Port,motor.IN1.pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(motor.IN2.Port,motor.IN2.pin, GPIO_PIN_SET);
		break;
	case OFF:
		HAL_GPIO_WritePin(motor.IN1.Port,motor.IN1.pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(motor.IN2.Port,motor.IN2.pin, GPIO_PIN_RESET);
		break;
	}
}
void setPowerMotor(int power, int motor) {
	if (motor == MOTOR_A) {
		TIM3->CCR4 = power;

	} else {
		TIM2->CCR1 = power;
	}
}

void enableMotor(motor motor){
	HAL_GPIO_WritePin(motor.EN.Port,motor.EN.pin, GPIO_PIN_SET);
}
void disableMotor(motor motor){
	HAL_GPIO_WritePin(motor.EN.Port,motor.EN.pin, GPIO_PIN_RESET);
}




