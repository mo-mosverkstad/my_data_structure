#include <string.h>
#include "dynamic_stack.h"
#include "result.h"

bool apply_op(dynamic_stack *stk, char op) {
    Result B = dynamic_stack_pop(stk);
    Result A = dynamic_stack_pop(stk);
    if (!A.success || !B.success) return false;
    int result;
    switch(op) {
        case '+': result = A.value + B.value; break;
        case '-': result = A.value - B.value; break;
        case '*': result = A.value * B.value; break;
        case '/': result = A.value / B.value; break;
    }
    dynamic_stack_push(stk, result);
    return true;
}

int main() {
    dynamic_stack *stk = dynamic_stack_new(16);
    printf("HP-35 pocket calculator\n");
    int n = 16;
    char *buffer = malloc(n);
    bool running = true;
    while(running) {
        printf(" > ");
        fgets(buffer, n, stdin);
        if (strcmp(buffer, "\n") == 0) {
            running = false;
        }
        else if (strchr("+-*/", buffer[0]) && buffer[1] == '\n') {
            if (!apply_op(stk, buffer[0])) {
                printf("PROBLEM: STACK PROBLEM\n\n");
                running = false;
            }
        }
        else {
            int val = atoi(buffer);
            dynamic_stack_push(stk, val);
        }
        printf("Stack: ");
        dynamic_stack_print(stk);
    }
    Result final_result = dynamic_stack_pop(stk);
    if (final_result.success){
        printf("SUCCESS: The result is: %d\n", final_result.value);
    }
    else{
        printf("PROBLEM: STACK PROBLEM\n");
    }
    free(buffer);
    dynamic_stack_delete(stk);
}
