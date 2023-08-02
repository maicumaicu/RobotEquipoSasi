/*
 * motors.h
 *
 *  Created on: Jul 24, 2023
 *      Author: jore
 */

#ifndef INC_MOTORS_H_
#define INC_MOTORS_H_
#include "stm32f1xx_hal.h"
#include "Defines.h"

void runMotor(int dir, motor motor);
void enableMotor(motor motor);
void disableMotor(motor motor);
void setMotorPower(int power,TIM_TypeDef* TIMX,uint32_t CCRX );



#endif /* INC_MOTORS_H_ */

