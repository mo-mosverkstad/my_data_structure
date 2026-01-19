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

dynamic_stack *dynamic_stack_new(unsigned int size) {
    dynamic_stack *stk = malloc(sizeof(dynamic_stack));
    if (!stk) return NULL;
    stk->array = malloc(size * sizeof(int));
    if (!stk->array) {
        free(stk);
        return NULL;
    }
    stk->top = 0;
    stk->size = size;
    return stk;
}

void dynamic_stack_delete(dynamic_stack *stk) {
    if (!stk) return;
    free(stk->array);
    free(stk);
}

bool dynamic_stack_push(dynamic_stack *stk, int val) {
    if (stk->top >= stk->size) {
        unsigned int new_size = stk->size * 2;
        int *new_array = malloc(new_size * sizeof(int));
        if (!new_array){
            return false;
        }
        for (unsigned int i = 0; i < stk->top; i++){
            new_array[i] = stk->array[i];
        }
        free(stk->array);
        stk->array = new_array;
        stk->size = new_size;
    }
    stk->array[stk->top++] = val;
    return true;
}

Result dynamic_stack_pop(dynamic_stack *stk) {
    if (stk->top == 0) {
        return (Result){ .success = false, .value = 0 };
    }
    
    int popped = stk->array[--stk->top];
    if (stk->top > 0 && stk->top < stk->size/4 && stk->size > MIN_STACK_SIZE){
        unsigned int new_size = stk->size / 2;
        int *new_array = malloc(new_size * sizeof(int));
        if (new_array){
            for (unsigned int i = 0; i < stk->top; i++){
                new_array[i] = stk->array[i];
            }
            free(stk->array);
            stk->array = new_array;
            stk->size = new_size;
        }
    }
    return (Result){ .success = true, .value = popped };
}

void dynamic_stack_print(dynamic_stack* stk){
    printf("dynamic_stack(%d)[", stk->size);
    if (stk->top > 0){
        for (unsigned int i = 0; i < stk->top-1; i++){
            printf("%d, ", stk->array[i]);
        }
        printf("%d", stk->array[stk->top-1]);
    }
    printf("]\n");
}