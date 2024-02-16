/*
 * Defines.h
 *
 *  Created on: Jul 25, 2023
 *      Author: jore
 */

#ifndef INC_DEFINES_H_
#define INC_DEFINES_H_

// Structs

typedef struct{
	GPIO_TypeDef *Port;
	uint16_t pin;
} pin;

typedef struct {
	pin IN2;
	pin IN1;
	pin EN;
} motor;

typedef struct {
	pin PIN;
	int estado;
	int flag;
} button;

//Defines

#define ADELANTE 0
#define ATRAS 1
#define OFF 2

#define MOTOR_A 0
#define MOTOR_B 1

#define CANT_BTN 4
#define ESPERA 0
#define CONFIRMACION 1
#define LIBERACION 2
#define TICKS_BTN  25

#define cant_sensores 7

#define INIT 0
#define MAIN 1
#define SECUENCIA_INICIO 2

#define DERECHA 0
#define IZQUIERDA 1

#define ADC_BUF_LEN 100

#define BLANCO 0
#define NEGRO 1

#define TIEMPO_VUELTA 1000
// Externs






#endif /* INC_DEFINES_H_ */
