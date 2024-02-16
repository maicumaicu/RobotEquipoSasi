/*
 * movement.h
 *
 *  Created on: 14 ene. 2023
 *      Author: jore
 */

#ifndef INC_NODECONTROL_H_
#define INC_NODECONTROL_H_
#include "main.h"

void CreateNode(Node* m, float Sensors[4], int direcciones[4], float maxDistance[3]);
void moveNode(int lado, Position *a);
void EliminateNode(Node *m, Node* l, int d);




#endif /* INC_NODECONTROL_H_ */
