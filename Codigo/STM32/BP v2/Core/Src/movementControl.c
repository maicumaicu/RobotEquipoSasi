/*
 * movementControl.c
 *
 *  Created on: 14 ene. 2023
 *      Author: jore
 */

#include "movementControl.h"
#include "defs.h"
#include "main.h"

float offset = 0;
int giro = 0;
void rotateAxis(int direccion, int direcciones[4]) {
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

void resetAxis(int direcciones[4]) {
	for (int i = 0; i < 4; i++) {
		direcciones[i] = i;
	}
}

void movementMachine(int move) {
	switch (movementState) {
	case OFF:
		/*runMotor(OFF, MOTOR_A);
		runMotor(OFF, MOTOR_B);*/
		if (move != OFF) {
			movementState = move;
			if (move != ADELANTE) {
				 /*TIM3->CNT = 3000;
				 TIM1->CNT = 3000;
				 offset = 753;*/
				TIM3->CNT = 0;
				TIM1->CNT = 0;
				offset = 0;

			} else {
				TIM3->CNT = 100;
				TIM1->CNT = 100;
				offset = 25.1;
			}
			//intUartSend(TIM3->CNT);
		}
		break;
	case ADELANTE:
		//TIM4->CCR3 = xSpeed;
		//TIM4->CCR4 = xSpeed;
		intUartSend(TIM1->CNT);

		objectiveDistance = forwardChoice[choice] + offset;
		//acelerationObjective = offset;
		//if (Sensors[2] > 5) {
		if (((calcularDistancia((TIM3->CNT) >> 1)
				+ calcularDistancia((TIM1->CNT) >> 1)) / 2
				< forwardChoice[choice] + offset
				|| (calcularDistancia((TIM3->CNT) >> 1)
						+ calcularDistancia((TIM1->CNT) >> 1)) / 2
						> forwardChoice[choice] + offset + 0.5 ) ){
			//moveStraight();
			StraightFlag = 1;
			KPP = KPPchoice[SLOW];
			KDP = KDPchoice[SLOW];

			//intUartSend(objectiveDistance -(calcularDistancia(TIM3->CNT) + calcularDistancia(TIM1->CNT))/2);
			//intUartSend(1);
			if (direction == ADELANTE) {
				runMotor(ADELANTE, MOTOR_A);
				runMotor(ADELANTE, MOTOR_B);
			} else {
				runMotor(ATRAS, MOTOR_A);
				runMotor(ATRAS, MOTOR_B);
			}

		} else {
			StraightFlag = 0;
			movimientoFlag = 1;
			movementState = OFF;
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			intUartSend(offset);
			aceleration = ADELANTE;
			//TIM3->CNT = 0;
			//TIM1->CNT = 0;

			/*offset = (calcularDistancia((TIM3->CNT) >> 1)
					+ calcularDistancia((TIM1->CNT) >> 1)) / 2;*/
			//HAL_Delay(2000);

			//intUartSend(10);
		}
		/*} else {
		 StraightFlag = 0;
		 movimientoFlag = 2;
		 movementState = OFF;
		 offset = (calcularDistancia((TIM3->CNT) >> 1)
		 + calcularDistancia((TIM1->CNT) >> 1)) / 2;

		 }*/
		break;
	case IZQUIERDA:
		TIM4->CCR3 = baseChoice[choice]
				- (calcularDistancia((TIM3->CNT) >> 1)
						* (baseChoice[choice] / LeftChoice[choice])
						- baseChoice[choice] / 1.8);
		TIM4->CCR4 = baseChoice[choice]
				- (calcularDistancia((TIM3->CNT) >> 1)
						* (baseChoice[choice] / LeftChoice[choice])
						- baseChoice[choice] / 1.8);
		//intUartSend((TIM3->CNT));
		if (calcularDistancia((TIM3->CNT) >> 1) < LeftChoice[choice]) {
			runMotor(ADELANTE, MOTOR_A);
			runMotor(ATRAS, MOTOR_B);
		} else {
			movementState = ADELANTE;
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			TIM3->CNT = 100;
			TIM1->CNT = 100;
			offset = 25.1;
			//giro = 1;
			//intUartSend(9);
		}
		break;
	case DERECHA:
		TIM4->CCR3 = xSpeed;
		TIM4->CCR4 = xSpeed;
		//intUartSend(TIM1->CNT);
		objectiveDistance = RightChoice[choice] + offset;
		if (calcularDistancia((TIM1->CNT) >> 1) < RightChoice[choice] + offset
				|| calcularDistancia((TIM1->CNT) >> 1)
						> RightChoice[choice] + offset + 0.5) {

			StraightFlag = 2;
			KPP = KPPchoice[TURN_90];
			KDP = KDPchoice[TURN_90];
			if (direction == ADELANTE) {
				runMotor(ATRAS, MOTOR_A);
				runMotor(ADELANTE, MOTOR_B);
			} else {
				runMotor(ADELANTE, MOTOR_A);
				runMotor(ATRAS, MOTOR_B);
			}
			//intUartSend("HOLA");
		} else {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
			movementState = ADELANTE;
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			TIM3->CNT = 100;
			TIM1->CNT = 100;
			offset = 25.1;
			//intUartSend(8);
		}
		break;
	case ATRAS:
		TIM4->CCR3 = xSpeed;
		TIM4->CCR4 = xSpeed;
		objectiveDistance = RightChoice[choice] * 2 + offset;
		if (calcularDistancia((TIM1->CNT) >> 1)
				< RightChoice[choice] * 2 + offset
				|| calcularDistancia((TIM1->CNT) >> 1)
						> RightChoice[choice] * 2 + 0.5 + offset) {

			StraightFlag = 2;
			KPP = KPPchoice[TURN_90];
			KDP = KDPchoice[TURN_90];
			if (direction == ADELANTE) {
				runMotor(ATRAS, MOTOR_A);
				runMotor(ADELANTE, MOTOR_B);
			} else {
				runMotor(ADELANTE, MOTOR_A);
				runMotor(ATRAS, MOTOR_B);
			}

		} else {

			StraightFlag = 0;
			movementState = ADELANTE;
			runMotor(OFF, MOTOR_A);
			runMotor(OFF, MOTOR_B);
			TIM3->CNT = 100;
			TIM1->CNT = 100;
			offset = 25.1;
			//intUartSend(7);
		}
		break;

	}
}

