/*
 * sharp.h
 *
 *  Created on: Aug 21, 2022
 *      Author: usuario
 */

#ifndef INC_SHARP_H_
#define INC_SHARP_H_
#include "stm32f1xx_hal.h"
#include "main.h"


uint32_t * readSensor(uint32_t *value);
float lecSensor(int n, uint32_t *values);

#endif /* INC_SHARP_H_ */
