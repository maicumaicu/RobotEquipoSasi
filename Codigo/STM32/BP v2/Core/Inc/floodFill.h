/*
 * floodFill.h
 *
 *  Created on: Feb 1, 2023
 *      Author: jore
 */

#ifndef INC_FLOODFILL_H_
#define INC_FLOODFILL_H_

#include "main.h"

struct Stack {
  int top;
  unsigned capacity;
  Position *array;
};

void floodfill(struct Stack *stack, Node  Map[4][4]);
Position peek(struct Stack *stack);
Position pop(struct Stack *stack);
void push(struct Stack *stack, Position item);
int isEmpty(struct Stack *stack);
int isFull(struct Stack *stack);
struct Stack *createStack(unsigned capacity);

int j, finish;
int dis;
Position pos;
Position posPrev;
Position p;





#endif /* INC_FLOODFILL_H_ */
