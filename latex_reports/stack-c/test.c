#include "static_stack.h"
#include "dynamic_stack.h"
#include "result.h"

int main() {
    // static stack testing
    printf("--- TESTING STATIC STACK ---\n");
    static_stack *stk1 = static_stack_new(4);
    static_stack_push(stk1, 32);
    static_stack_push(stk1, 33);
    static_stack_push(stk1, 34);
    static_stack_push(stk1, 55);

    Result r = static_stack_pop(stk1);
    if (r.success) printf("stack_pop : %d\n", r.value);
    r = static_stack_pop(stk1);
    if (r.success) printf("stack_pop : %d\n", r.value);
    r = static_stack_pop(stk1);
    if (r.success) printf("stack_pop : %d\n", r.value);

    static_stack_print(stk1);
    static_stack_delete(stk1);
    printf("\n");

    // dynamic stack testing

    printf("--- TESTING DYNAMIC STACK ---\n");
    dynamic_stack *stk2 = dynamic_stack_new(MIN_STACK_SIZE);
    for (int i = 0; i < 105; i++){
        bool result = dynamic_stack_push(stk2, i);
        if (!result){
            printf("PROBLEM: Push problem");
            break;
        }
    }

    for (int i = 0; i < 82; i++){
        Result r = dynamic_stack_pop(stk2);
        if (r.success){
            printf("stack_pop : %d\n", r.value);
        }
        else{
            printf("PROBLEM: Pop problem");
            break;
        }
    }

    dynamic_stack_print(stk2);
    dynamic_stack_delete(stk2);
}