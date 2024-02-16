/*
 * movementControl.h
 *
 *  Created on: 14 ene. 2023
 *      Author: jore
 */

#ifndef INC_MOVEMENTCONTROL_H_
#define INC_MOVEMENTCONTROL_H_
#include "main.h"
#include "sharp.h"
#include "motors.h"
#include "nodeControl.h"
void rotateAxis(int direccion,int direcciones[4]);
void resetAxis(int direcciones[4]);
void movementMachine(int move);



#endif /* INC_MOVEMENTCONTROL_H_ */
