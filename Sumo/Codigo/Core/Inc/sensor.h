/*
 * sensor.h
 *
 *  Created on: Jul 24, 2023
 *      Author: jore
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include "stm32f1xx_hal.h"
#include "Defines.h"

int* readSensorsArray(pin* sensors, int cuantity);
int readSensor(pin sensor);
int lecturaCNY70(int n, uint32_t values[100]);



#endif /* INC_SENSOR_H_ */
