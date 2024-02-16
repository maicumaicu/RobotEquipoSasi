/*
 * motors.h
 *
 *  Created on: Aug 15, 2022
 *      Author: usuario
 */

#ifndef INC_MOTORS_H_
#define INC_MOTORS_H_
#include "stm32f1xx_hal.h"
#include "main.h"

void setPowerMotor(int power, int motor);
void runMotor(int dir, int motor);
float calcularDistancia(int counter);
void runForward();
void runBackwards();
void runRight();
void runLeft();
void runOff();
#endif /* INC_MOTORS_H_ */
