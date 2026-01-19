#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "result.h"

#define MIN_STACK_SIZE 4

typedef struct dynamic_stack{
    unsigned int top;
    unsigned int size;
    int *array;
} dynamic_stack;

dynamic_stack *dynamic_stack_new(unsigned int size);
void dynamic_stack_delete(dynamic_stack *stk);
bool dynamic_stack_push(dynamic_stack *stk, int val);
Result dynamic_stack_pop(dynamic_stack *stk);
void dynamic_stack_print(dynamic_stack* stk);

#endif