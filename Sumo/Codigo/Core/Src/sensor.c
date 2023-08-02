/*
 * sensor.c
 *
 *  Created on: Jul 24, 2023
 *      Author: jore
 */
#include "sensor.h"
#include "stdlib.h"
#include "main.h"


int readSensor(pin sensor) {
	return HAL_GPIO_ReadPin(sensor.Port, sensor.pin);
}

int* readSensorsArray(pin *sensors, int cuantity) {
	int *S = (int*) malloc(sizeof(int) * cuantity);
	for (int i = 0; i < cuantity; i++) {
		S[i] = readSensor(sensors[i]);
	}
	return S;
}

int lecturaCNY70(int n, uint32_t values[10]) {
	long suma = 0;
	for (int i = 0; i < n; i++) {
		suma = suma + values[i];
	}
	int adc = (suma / n);
	if (adc < 400) {
		return BLANCO;
	} else {
		return NEGRO;
	}
}

