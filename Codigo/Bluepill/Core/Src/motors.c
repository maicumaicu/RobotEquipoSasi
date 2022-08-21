/*
 * motors.c
 *
 *  Created on: Aug 15, 2022
 *      Author: usuario
 */
#include "motors.h"


int counterD, counterI;

float calcularDistancia(int counter) {
  return ((counter- 32767.5) * 2.51 / 10);
}

void movementMachine(int move) {
  switch (movementState) {
    case OFF:
      runOff();
      //degrees = 0;
      //offset = getTurnAngle();
      if (move != OFF) {
        movementState = move;
        counterI = TIM1->CNT = 0;
        counterD = TIM4->CNT = 0;
      }
      break;
    case ADELANTE:
      //SerialBT.print(calcularDistancia(counterI));
      if (calcularDistancia(counterD) < FORWARD_DISTANCE  || calcularDistancia(counterI) < FORWARD_DISTANCE) {
        //estabilizacion();
        //powerA = 100;
        //powerB = 100;
        runForward();
        //SerialBT.print(calcularDistancia(counterI));
        //SerialBT.print("  ");
        //SerialBT.println(calcularDistancia(counterD));
      } else {
        //estabilizationOffset = getTurnAngle();
        movimientoFlag = 1;
        movementState = OFF;
        //SerialBT.print("listo");
      }
      break;
    /*case IZQUIERDA:

      //SerialBT.println("IZQUIERDA");
      //degrees = getTurnAngle();
      //SerialBT.println(degrees);
      if (degrees  <= LEFT_ANGLE_MIN + offset) {
        //SerialBT.println(degrees);
        //SerialBT.println(counterD);
        powerA = TURN_VELOCITY_I;
        powerB = TURN_VELOCITY_D;
        runLeft(powerA, powerB);
      } else if (degrees  >= LEFT_ANGLE_MAX + offset) {
        runRight(powerA, powerB);
      } else {
        //runOff(0, 0);
        estabilizationOffset = getTurnAngle();
        movementState = ADELANTE;
        counterD = 0;
        counterI = 0;
      }
      break;
    case DERECHA:
      //SerialBT.println("DERECHA");
      degrees = abs(getTurnAngle());
      SerialBT.println(degrees);
      if (degrees  <= (LEFT_ANGLE_MIN) + offset) {
        powerA = TURN_VELOCITY_I;
        powerB = TURN_VELOCITY_D;
        runRight(powerA, powerB);
      } else if (degrees  >= LEFT_ANGLE_MAX + offset) {
        runLeft(powerA, powerB);
      } else {
        estabilizationOffset = getTurnAngle();
        movementState = ADELANTE;
        //runOff(0, 0);
        counterD = 0;
        counterI = 0;
      }
      break;
    case ATRAS:
      //SerialBT.println("ATRAS");
      //degrees = getTurnAngle();
      //SerialBT.println(degrees);
      if (degrees  <= -(LEFT_ANGLE_MIN) * 2 + offset || degrees  >= -(LEFT_ANGLE_MAX) * 2 + offset) {
        powerA = 50;
        powerB = 50;
        runRight(powerA, powerB);
      } else {
        movementState = ADELANTE;
        counterD = 0;
        counterI = 0;
      }
      break;
    case SUPER:
      int X = directions[m] - '0';
      if (calcularDistancia(counterD) < FORWARD_DISTANCE * X  && calcularDistancia(counterI) < FORWARD_DISTANCE * X) {
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


void runForward() {
	runMotor(ADELANTE, MOTOR_A);
	runMotor(ADELANTE, MOTOR_B);
}

void runBackwards() {
	runMotor(ATRAS, MOTOR_A);
	runMotor(ATRAS, MOTOR_B);
}

void runRight() {
	runMotor(ADELANTE, MOTOR_A);
	runMotor(OFF, MOTOR_B);
}

void runLeft() {
	runMotor(OFF, MOTOR_A);
	runMotor(ADELANTE, MOTOR_B);
}

void runOff() {
	runMotor(OFF, MOTOR_A);
	runMotor(OFF, MOTOR_B);
}

void setPowerMotor(int power, int motor) {
	if (motor == MOTOR_A) {
		TIM4->CCR4 = power;

	} else {
		TIM4->CCR3 = power;
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

