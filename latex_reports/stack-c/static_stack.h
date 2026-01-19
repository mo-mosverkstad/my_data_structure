#ifndef STATIC_STACK_H
#define STATIC_STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "result.h"

typedef struct static_stack{
    unsigned int top;
    unsigned int size;
    int *array;
} static_stack;

static_stack *static_stack_new(unsigned int size);
void static_stack_delete(static_stack *stk);
bool static_stack_push(static_stack *stk, int val);
Result static_stack_pop(static_stack *stk);
void static_stack_print(static_stack* stk);

#endif