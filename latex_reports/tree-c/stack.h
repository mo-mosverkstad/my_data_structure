#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>
#include "tree.h"

typedef struct stack {
    node **elements;
    size_t capacity;
    size_t top;
} stack;

stack *stack_create(void);
void stack_free(stack *stk);
void stack_push(stack *stk, node *nd);
node *stack_pop(stack *stk);
bool stack_empty(const stack *stk);

#endif
