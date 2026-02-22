#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

stack *stack_create(void) {
    stack *stk = (stack *) malloc(sizeof(stack));
    if (stk == NULL) {
        perror("Malloc stack control block failure");
        exit(EXIT_FAILURE);
    }
    stk->capacity = 16;
    stk->top = 0;
    stk->elements = (node **) malloc(stk->capacity * sizeof(node *));
    if (stk->elements == NULL) {
        perror("Malloc array elements failure");
        exit(EXIT_FAILURE);
    }
    return stk;
}

void stack_free(stack *stk) {
    if (stk != NULL) {
        free(stk->elements);
        free(stk);
    }
}

void stack_push(stack *stk, node *nd) {
    if (stk->top == stk->capacity) {
        size_t new_capacity = stk->capacity * 2;
        node **new_elements = (node **) realloc(stk->elements, new_capacity * sizeof(node *));
        if (new_elements == NULL) {
            perror("Stack growth by realloc failure");
            exit(EXIT_FAILURE);
        }
        stk->elements = new_elements;
        stk->capacity = new_capacity;
    }
    stk->elements[stk->top++] = nd;
}

bool stack_empty(const stack *stk) {
    return stk->top == 0;
}

node *stack_pop(stack *stk) {
    if (stk->top == 0) return NULL;
    return stk->elements[--stk->top];
}
