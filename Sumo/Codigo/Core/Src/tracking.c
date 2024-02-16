/*
 * tracking.c
 *
 *  Created on: Jul 25, 2023
 *      Author: jore
 */

#include "tracking.h"
#include "stm32f1xx_hal.h"
#include "UsefulFunctions.h"

float pid, elapsedTime, pidP, pidD, errorP, timeNowP, timePrevP, previousErrorP;
int motLeft, motRight;
int velocity = 1000;
float KPT = 1;
float KDT = 1;
float KPL = 1;
float KDL = 1;
int xSpeed;

int targetPosition(int *mediciones) {
	return (mediciones[0] + mediciones[1] + mediciones[2] + mediciones[3]
			+ mediciones[4]) != 0 ?
			((4000 * mediciones[0] + 3000 * mediciones[1] + 2000 * mediciones[2]
					+ 1000 * mediciones[3] + 0 * mediciones[4])
					/ (mediciones[0] + mediciones[1] + mediciones[2]
							+ mediciones[3] + mediciones[4])) :
			-1;
}

int linePosition(int *mediciones) {
	return (mediciones[0] + mediciones[1] + mediciones[2] + mediciones[3])
			!= 0 ?
			((-1000 * mediciones[0] - 2000 * mediciones[1]
					+ 2000 * mediciones[2] + 1000 * mediciones[3])) :
			-1;
}

void targetTracking(int position) {
	errorP = position - 2000;
	timePrevP = timeNowP;
	timeNowP = HAL_GetTick();
	elapsedTime = (timeNowP - timePrevP) / 1000;
	pidD = KDT * ((errorP - previousErrorP) / elapsedTime);
	pidP = KPT * errorP;
	pid = pidP + pidD;
	if (pid > velocity) {
		//intUartSend(1);
		pid = velocity;
	}
	if (pid < -velocity) {
		//intUartSend(0);
		pid = -velocity;
	}
	motLeft = velocity - pid;
	motRight = velocity + pid;
	if (motLeft < -1000) {
		motLeft = -1000;
	}
	if (motRight < -1000) {
		motRight = -1000;
	}

	previousErrorP = errorP;
	motRight = constrain(motRight, -1000, 1000);
	motLeft = constrain(motLeft, -1000, 1000);

	motRight = MAP(motRight, -1000, 1000, MINVELOCITY, MAXVELOCITY);
	motLeft = MAP(motLeft, -1000, 1000, MINVELOCITY, MAXVELOCITY);

	if (motRight < MINVELOCITY) {
		motRight = MINVELOCITY;
	}

	if (motLeft < MINVELOCITY) {
		motLeft = MINVELOCITY;
	}
	if (position != -1) {
		TIM3->CCR4 = motRight;
		TIM2->CCR1 = motLeft;
	} else {
		TIM3->CCR4 = 60535;
		TIM2->CCR1 = 65535;
	}
}

void lineTracking(int position) {

	errorP = position;

	timePrevP = timeNowP;
	timeNowP = HAL_GetTick();
	elapsedTime = (timeNowP - timePrevP) / 1000;
	pidD = KDL * ((errorP - previousErrorP) / elapsedTime);
	pidP = KPL * errorP;
	pid = pidP + pidD;
	if (pid > velocity) {
		//intUartSend(1);
		pid = velocity;
	}
	if (pid < -velocity) {
		//intUartSend(0);
		pid = -velocity;
	}
	motLeft = velocity - pid;
	motRight = velocity + pid;
	if (motLeft < -1000) {
		motLeft = -1000;
	}
	if (motRight < -1000) {
		motRight = -1000;
	}

	previousErrorP = errorP;
	motRight = constrain(motRight, -1000, 1000);
	motLeft = constrain(motLeft, -1000, 1000);

	motRight = MAP(motRight, -1000, 1000, MINVELOCITY, MAXVELOCITY);
	motLeft = MAP(motLeft, -1000, 1000, MINVELOCITY, MAXVELOCITY);

	if (motRight < MINVELOCITY) {
		motRight = MINVELOCITY;
	}

	if (motLeft < MINVELOCITY) {
		motLeft = MINVELOCITY;
	}
	if (position != 0) {
		TIM3->CCR4 = motRight;
		TIM2->CCR1 = motLeft;
	} else {
		TIM3->CCR4 = 65535;
		TIM2->CCR1 = 60000;
	}

}
