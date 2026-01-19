#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct static_stack{
    unsigned int top;
    unsigned int size;
    int *array;
} static_stack;

typedef struct PopResult{
    bool success;
    int value;
} PopResult;

static_stack *static_stack_new(unsigned int size) {
    static_stack *stk = malloc(sizeof(static_stack));
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

void static_stack_delete(static_stack *stk) {
    if (!stk) return;
    free(stk->array);
    free(stk);
}

// true if success, false if failed operation
bool static_stack_push(static_stack *stk, int val) {
    if (stk->top >= stk->size) {
        return false;
    }
    stk->array[stk->top++] = val;
    return true;
}

PopResult static_stack_pop(static_stack *stk) {
    if (stk->top == 0) {
        return (PopResult){ .success = false, .value = 0 };
    }
    return (PopResult){ .success = true, .value = stk->array[--stk->top] };
}

void static_stack_print(static_stack* stk){
    printf("[");
    if (stk->top > 0){
        for (int i = 0; i < stk->top-1; i++){
            printf("%d, ", stk->array[i]);
        }
        printf("%d", stk->array[stk->top-1]);
    }
    printf("]\n");
}


int main() {
    static_stack *stk = static_stack_new(4);
    static_stack_push(stk, 32);
    static_stack_push(stk, 33);
    static_stack_push(stk, 34);
    static_stack_push(stk, 55);

    PopResult r;
    r = static_stack_pop(stk);
    if (r.success) printf("stack_pop : %d\n", r.value);
    r = static_stack_pop(stk);
    if (r.success) printf("stack_pop : %d\n", r.value);
    r = static_stack_pop(stk);
    if (r.success) printf("stack_pop : %d\n", r.value);

    static_stack_print(stk);
    static_stack_delete(stk);
}