#include <stdlib.h>
#include <stdio.h>

// static stack

typedef struct stack {
    int top;
    int size;
    int *array;
} stack;

stack *new_stack(int size) {
    int *array = (int*) malloc(size*sizeof(int));
    stack *stk = (stack*) malloc(sizeof(stack));
    ...
    return stk;
}

void push(stack *stk, int val) {
    ...
}

int pop(stack *stk) {
    ...
}

int main() {
    stack *stk = new_stack(4);
    push(stk, 32);
    push(stk, 33);
    push(stk, 34);
    printf("pop : %d\n", pop(stk));
    printf("pop : %d\n", pop(stk));
    printf("pop : %d\n", pop(stk));
}

// does it work???

int main() {
    stack *stk = stack(4);
    int n = 10;
    for(int i = 0; i < n; i++) {
        push(stk, i+30);
    }
    for(int i = 0; i < stk->top; i++) {
        printf("stack[%d] : %d\n", i, stk->array[i]);
    }
    int val = pop(stk);
    while(val != 0) { // assuming 0 is returned when the stack is empty
        printf("pop : %d\n", val);
        val = pop(stk);
    }
}
