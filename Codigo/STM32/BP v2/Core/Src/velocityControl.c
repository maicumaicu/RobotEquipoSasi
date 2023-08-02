/*
 * velocityControl.c
 *
 *  Created on: 15 ene. 2023
 *      Author: jore
 */
#include "velocityControl.h"
#include "movementControl.h"
#include "main.h"

float pid, elapsedTime, pidP, pidD;
float errorT, errorA, errorP, previousErrorT, previousErrorA, previousErrorP;
float timeNowT, timePrevT, timeNowA, timePrevA, timeNowP, timePrevP;
int motLeft, motRight;
int pLeft = 1;
int pRight = 1;

void aproximationPID(int sentido) {
	if (sentido == ADELANTE) {
			errorP = objectiveDistance
							- (calcularDistancia((TIM1->CNT) >> 1)
									+ calcularDistancia((TIM3->CNT) >> 1)) / 2;
	} else if (sentido == IZQUIERDA) {
		errorP =   objectiveDistance - calcularDistancia((TIM3->CNT) >> 1);
	} else {
		errorP =  objectiveDistance - calcularDistancia((TIM1->CNT) >> 1) ;
	}

	timePrevP = timeNowT;
	timeNowP = HAL_GetTick();
	elapsedTime = (timeNowP - timePrevP) / 1000;
	pidD = KDP * ((errorP - previousErrorP) / elapsedTime);
	pidP = KPP * errorP;
	pid = pidP + pidD;
	if (pid > velocity) {
		//intUartSend(1);
		pid = velocity;
	}
	if (pid < -velocity) {
		//intUartSend(0);
		pid = -velocity;
	}
	xSpeed = pid;
	if (xSpeed < -1000) {
		xSpeed = -1000;
	}

	previousErrorT = errorT;
	xSpeed = constrain(xSpeed, -1000, 1000);
	xSpeed = MAP(xSpeed, -1000, 1000, -baseChoice[choice], baseChoice[choice]);
	if (xSpeed >= 0) {
		direction = ADELANTE;

	} else {
		xSpeed = -xSpeed;
		direction = ATRAS;
	}
	if (xSpeed < 10000) {
		xSpeed = 10000;
	}

	if (xSpeed == baseChoice[choice]){
		aceleration = ATRAS;
	}
}

void angularPID() {
	 if (Sensors[3] > maxDistance[1] && Sensors[1] < maxDistance[2]) {
		//intUartSend(0);
		errorA = Sensors[1] - CenterDistanceRight;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
	} else if (Sensors[3] < maxDistance[1]
			&& Sensors[1] > maxDistance[2]) {
		//intUartSend(1);

		errorA = CenterDistanceLeft - Sensors[3];
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
	} else if (Sensors[1] > maxDistance[2]  && Sensors[3] > maxDistance[1]){
		//intUartSend(3);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
		errorA = 0;
	} else if(Sensors[3] > CenterDistanceLeft){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
		errorA = Sensors[1] - CenterDistanceRight;
	}else {

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
		errorA = CenterDistanceLeft - Sensors[3];

	}
	timePrevA = timeNowA;
	timeNowA = HAL_GetTick();
	elapsedTime = (timeNowA - timePrevA) / 1000;
	pidD = KDA * ((errorA - previousErrorA) / elapsedTime);
	pidP = KPA * errorA;
	pid = pidP + pidD;

	if (pid > 100) {
		//intUartSend(1);
		pid = 100;
	}
	if (pid < -100) {
		//intUartSend(0);
		pid = -100;
	}
	pLeft = (100 - pid)/100;
	pRight = (100 + pid)/100;
	previousErrorA = errorA;
}

void moveStraight() {
	if (StraightFlag == 1) {
		errorT = calcularDistancia((TIM1->CNT) >> 1) * pLeft
				- calcularDistancia((TIM3->CNT) >> 1) * pRight;
	}else if (StraightFlag == 2){
		errorT = (offset - calcularDistancia((TIM1->CNT) >> 1))
						+ (offset - calcularDistancia((TIM3->CNT) >> 1));
	}

	timePrevT = timeNowT;
	timeNowT = HAL_GetTick();
	elapsedTime = (timeNowT - timePrevT) / 1000;
	pidD = KDT * ((errorT - previousErrorT));
	pidP = KPT * errorT;
	pid = pidP + pidD;
	if (pid > velocity) {
		//intUartSend(1);
		pid = velocity;
	}
	if (pid < -velocity) {
		//intUartSend(0);
		pid = -velocity;
	}
	//intUartSend(pid);
	//HAL_Delay(10);

	motLeft = velocity - pid;
	motRight = velocity + pid;


	previousErrorT = errorT;
	motRight = constrain(motRight, -1000, 1000);
	motLeft = constrain(motLeft, -1000, 1000);

	motRight = MAP(motRight, -1000, 1000, 0, xSpeed * 2);
	motLeft = MAP(motLeft, -1000, 1000, 0, xSpeed * 2);

	TIM4->CCR4 = motLeft;
	TIM4->CCR3 = motRight;
}

