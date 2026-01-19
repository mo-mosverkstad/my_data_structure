#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct dynamic_stack{
    unsigned int top;
    unsigned int size;
    int *array;
} dynamic_stack;

typedef struct PopResult{
    bool success;
    int value;
} PopResult;

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
        for (int i = 0; i < stk->top; i++){
            new_array[i] = stk->array[i];
        }
        free(stk->array);
        stk->array = new_array;
        stk->size = new_size;
    }
    stk->array[stk->top++] = val;
    return true;
}

PopResult dynamic_stack_pop(dynamic_stack *stk) {
    if (stk->top == 0) {
        return (PopResult){ .success = false, .value = 0 };
    }
    return (PopResult){ .success = true, .value = stk->array[--stk->top] };
}

void dynamic_stack_print(dynamic_stack* stk){
    printf("(%d)[", stk->size);
    if (stk->top > 0){
        for (int i = 0; i < stk->top-1; i++){
            printf("%d, ", stk->array[i]);
        }
        printf("%d", stk->array[stk->top-1]);
    }
    printf("]\n");
}


int main() {
    dynamic_stack *stk = dynamic_stack_new(4);
    for (int i = 0; i < 105; i++){
        bool result = dynamic_stack_push(stk, i);
        if (!result){
            printf("PROBLEM: Push problem");
            break;
        }
    }

    PopResult r;
    for (int i = 0; i < 73; i++){
        r = dynamic_stack_pop(stk);
        if (r.success){
            printf("stack_pop : %d\n", r.value);
        }
        else{
            printf("PROBLEM: Pop problem");
            break;
        }
    }

    dynamic_stack_print(stk);
    dynamic_stack_delete(stk);
}