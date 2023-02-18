/*
 * floodFill.c
 *
 *  Created on: Feb 1, 2023
 *      Author: jore
 */

#include "main.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "floodFill.h"

Position p = {-1, -1};
Position posPrev = {-1, -1};
Position pos = {-1, -1};
int j, finish;
int dis;

struct Stack *createStack(unsigned capacity) {
  struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->array = (Position *)malloc(stack->capacity * sizeof(Position));
  return stack;
}

int isFull(struct Stack *stack) { return stack->top == stack->capacity - 1; }

// Stack is empty when top is equal to -1
int isEmpty(struct Stack *stack) { return stack->top == -1; }

void push(struct Stack *stack, Position item) {
  if (isFull(stack))
    return;
  stack->array[++stack->top] = item;
  printf("%d and %d pushed to stack\n", item.x, item.y);
}

Position pop(struct Stack *stack) {
  if (isEmpty(stack))
    return p;
  return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
Position peek(struct Stack *stack) {
  if (isEmpty(stack))
    return p;
  return stack->array[stack->top];
}

void floodfill(struct Stack *stack, Node  Map[4][4]) {
  //int paso;
  if (stack->top != -1) {
    for (int i = 0; i <= stack->top; i++) {
      posPrev = pos;
      pos = pop(stack);
      dis = Map[pos.x][pos.y].distance + 1;
      for (int x = 0; x < 4; x++) {
        if (Map[pos.x][pos.y].Lados[x] != 1) {
          switch (x) {
          case 0:
            if (Map[pos.x][pos.y - 1].distance > dis) {
              Map[pos.x][pos.y - 1].distance = dis;
              push(stack, (Position){pos.x, pos.y - 1});
            }
            break;
          case 1:
            if (Map[pos.x - 1][pos.y].distance > dis) {
              Map[pos.x - 1][pos.y].distance = dis;
              push(stack, (Position){pos.x - 1, pos.y});
            }
            break;
          case 2:
            if (Map[pos.x][pos.y + 1].distance > dis) {
              Map[pos.x][pos.y + 1].distance = dis;
              push(stack, (Position){pos.x, pos.y + 1});
            }
            break;
          case 3:

            if (Map[pos.x + 1][pos.y].distance > dis) {
              Map[pos.x + 1][pos.y].distance = dis;
              push(stack, (Position){pos.x + 1, pos.y});
            }

            break;
          }
        }
      }
    }
  } else {
    finish = 1;
  }
}
