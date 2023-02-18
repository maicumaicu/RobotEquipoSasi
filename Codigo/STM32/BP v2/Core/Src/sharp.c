/*
 * sharp.c
 *
 *  Created on: Aug 21, 2022
 *      Author: usuario
 */
#include "sharp.h"
#include "main.h"
#include <math.h>


int wallDetector(int n, int d, int maxDis[3]) {
	switch (d) {
	case ADELANTE:
		if (n < maxDis[0]) {

			return 1;
		} else {

			return 0;
		}
		break;

	case IZQUIERDA:
		if (n < maxDis[1]) {
			return 1;
		} else {
			return 0;
		}
		break;
	case DERECHA:
		if (n < maxDis[2]) {
			return 1;
		} else {
			return 0;
		}
		break;
	default:
		return 0;
		break;
	}
}

float lecturaSensor(int direccion, float values[4], int maxDis[3]) {
	switch (direccion) {
	case ADELANTE:
		return wallDetector(values[2], direccion, maxDis);
		break;
	case DERECHA:
		return wallDetector(values[1], direccion, maxDis);
		break;
	case IZQUIERDA:
		return wallDetector(values[3], direccion, maxDis);
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
	float volts = MAP(adc,900,3400,35,310);
	volts = volts/100;// value from sensor * (5/1024)
	if (volts <= 0.35)
		volts = 0.35;
	volts = pow(volts - 0.3, 0.5);/*convertimos a cm con un aproximacion grafica*/
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
	if (adc < 1000) {
		return BLANCO;
	} else {
		return NEGRO;
	}
}

