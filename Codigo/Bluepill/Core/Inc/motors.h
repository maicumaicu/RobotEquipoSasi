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

#define MOTOR_A 0
#define MOTOR_B 1


#define ADELANTE 0
#define IZQUIERDA 1
#define ATRAS 2
#define DERECHA 3
#define SUPER 4
#define OFF 5

#define FORWARD_DISTANCE 260
#define LEFT_ANGLE_MIN 90
#define LEFT_ANGLE_MAX 96
#define FORWARD_VELOCITY_I 40
#define FORWARD_VELOCITY_D 47
#define TURN_VELOCITY_D 50
#define TURN_VELOCITY_I 50

void toggleLed();
void setPowerMotor(int power, int motor);
void runMotor(int dir, int motor);
void runForward(int powerA, int powerB);
void runBackwards(int powerA, int powerB);
void runRight(int powerA, int powerB);
void runLeft(int powerA, int powerB);
void runOff(int powerA, int powerB);
#endif /* INC_MOTORS_H_ */
