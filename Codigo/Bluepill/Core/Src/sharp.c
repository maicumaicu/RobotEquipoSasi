/*
 * sharp.c
 *
 *  Created on: Aug 21, 2022
 *      Author: usuario
 */
#include "sharp.h"

#include <math.h>

int wallDetector(int n) {
	if (n < 17) {
		return 1;
	} else {
		return 0;
	}

}

float lecturaSensor(int direccion, uint32_t values[4]) {
	switch (direccion) {
	case ADELANTE:
		return wallDetector(values[2]);
		break;
	case DERECHA:
		return wallDetector(values[1]);
		break;
	case IZQUIERDA:
		return wallDetector(values[3]);
		break;
	case ATRAS:
		return 0;
		break;
	}
	return 15;
}

float lecSensor(int n, uint32_t values[10]) {
	long suma = 0;
	for (int i = 0; i < n; i++) {
		suma = suma + values[i];
	}
	float adc = suma / n;
	float volts = adc * 0.0008056640; // value from sensor * (5/1024)
	if (volts <= 0.35)
		volts = 0.35;
	volts = pow(volts - 0.3, 0.25);/*convertimos a cm con un aproximacion grafica*/
	volts = 27.5 / volts; /*no preguntar por los valores*/
	volts -= 18;

	return volts;

}

int lecturaCNY70(int n, uint32_t values[10]) {
	long suma = 0;
	for (int i = 0; i < n; i++) {
		suma = suma + values[i];
	}
	int adc = (suma / n);
	if (adc < 800) {
		return BLANCO;
	} else {
		return NEGRO;
	}
}

