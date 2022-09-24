/*
 * sharp.c
 *
 *  Created on: Aug 21, 2022
 *      Author: usuario
 */
#include "sharp.h"
#include <math.h>

uint32_t* readSensor(uint32_t *value) {
	uint32_t CNY70[10];
	uint32_t SHARP_1[10];
	uint32_t SHARP_2[10];
	uint32_t SHARP_3[10];
	static uint32_t Sensors[4];
	for (int i = 0; i < 10; i++) {
		CNY70[i] = value[i * 4];
		SHARP_1[i] = value[i * 4 + 1];
		SHARP_2[i] = value[i * 4 + 2];
		SHARP_3[i] = value[i * 4 + 3];
	}
	Sensors[0] = lecSensor(10, CNY70);
	Sensors[1] = lecSensor(10, SHARP_1);
	Sensors[2] = lecSensor(10, SHARP_2);
	Sensors[3] = lecSensor(10, SHARP_3);
	return Sensors;
}

int wallDetector(int n) {
	if (n < 25) {
		return 1;
	}
	return 0;
}

float lecturaSensor(int direccion, uint32_t *values) {
	switch (direccion) {
	case ADELANTE:
		return wallDetector(values[1]);
		break;
	case DERECHA:
		return wallDetector(values[2]);
		break;
	case IZQUIERDA:
		return wallDetector(values[3]);
		break;
	case ATRAS:
		return 0;
		break;
	}
	return 0;
}

float lecSensor(int n, uint32_t *values) {
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

