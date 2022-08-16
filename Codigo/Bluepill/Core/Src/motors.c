/*
 * motors.c
 *
 *  Created on: Aug 15, 2022
 *      Author: usuario
 */
#include "motors.h"


void runForward(int powerA, int powerB) {
  setPowerMotor(powerA, MOTOR_A);
  setPowerMotor(powerB, MOTOR_B);
  runMotor(ADELANTE, MOTOR_A);
  runMotor(ADELANTE, MOTOR_B);
}

void runBackwards(int powerA, int powerB) {
  setPowerMotor(powerA, MOTOR_A);
  setPowerMotor(powerB, MOTOR_B);
  runMotor(ATRAS, MOTOR_A);
  runMotor(ATRAS, MOTOR_B);
}

void runRight(int powerA, int powerB) {
  setPowerMotor(powerA, MOTOR_A);
  setPowerMotor(powerB, MOTOR_B);
  runMotor(ADELANTE, MOTOR_A);
  runMotor(OFF, MOTOR_B);
}

void runLeft(int powerA, int powerB) {
  setPowerMotor(powerA, MOTOR_A);
  setPowerMotor(powerB, MOTOR_B);
  runMotor(OFF, MOTOR_A);
  runMotor(ADELANTE, MOTOR_B);
}

void runOff(int powerA, int powerB) {
  setPowerMotor(0, MOTOR_A);
  setPowerMotor(0, MOTOR_B);
  runMotor(OFF, MOTOR_A);
  runMotor(OFF, MOTOR_B);
}


void setPowerMotor(int power, int motor) {
	if (motor == MOTOR_A) {
		PWMA->CCR2 = power;

	} else {
		PWMB->CCR1 = power;
	}
}

void runMotor(int dir, int motor) {
	switch (dir) {
	case ADELANTE:
		if (motor == MOTOR_A) {
			HAL_GPIO_WritePin(AIN1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(AIN2, GPIO_PIN_RESET);
		} else {
			HAL_GPIO_WritePin(BIN1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(BIN2, GPIO_PIN_RESET);
		}
		break;
	case ATRAS:
		if (motor == MOTOR_A) {
			HAL_GPIO_WritePin(AIN1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(AIN2, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(BIN1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(BIN2, GPIO_PIN_SET);
		}
		break;
	case OFF:
		if (motor == MOTOR_A) {
			HAL_GPIO_WritePin(AIN1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(AIN2, GPIO_PIN_RESET);
		} else {
			HAL_GPIO_WritePin(BIN1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(BIN2, GPIO_PIN_RESET);
		}
		break;
	}
}

