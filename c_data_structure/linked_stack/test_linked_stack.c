#include <stdio.h>
#include "linked_stack.h"
#include "../test_framework/test_framework.h"

int test_create_destroy() {
    struct linked_stack *stack = linked_stack_create();
    ASSERT_TRUE(stack != NULL);
    linked_stack_destroy(stack);
    return 1;
}

int test_push_pop() {
    struct linked_stack *stack = linked_stack_create();
    linked_stack_push(stack, 42);
    int result = linked_stack_pop(stack);
    ASSERT_EQ(42, result);
    linked_stack_destroy(stack);
    return 1;
}

int test_lifo_order() {
    struct linked_stack *stack = linked_stack_create();
    linked_stack_push(stack, 1);
    linked_stack_push(stack, 2);
    linked_stack_push(stack, 3);
    
    ASSERT_EQ(3, linked_stack_pop(stack));
    ASSERT_EQ(2, linked_stack_pop(stack));
    ASSERT_EQ(1, linked_stack_pop(stack));
    
    linked_stack_destroy(stack);
    return 1;
}

int test_pop_empty_stack() {
    struct linked_stack *stack = linked_stack_create();
    int result = linked_stack_pop(stack);
    ASSERT_EQ(0, result);
    linked_stack_destroy(stack);
    return 1;
}

int test_multiple_operations() {
    struct linked_stack *stack = linked_stack_create();
    
    linked_stack_push(stack, 10);
    linked_stack_push(stack, 20);
    ASSERT_EQ(20, linked_stack_pop(stack));
    
    linked_stack_push(stack, 30);
    ASSERT_EQ(30, linked_stack_pop(stack));
    ASSERT_EQ(10, linked_stack_pop(stack));
    
    linked_stack_destroy(stack);
    return 1;
}

int test_example_sequence() {
    struct linked_stack *stack = linked_stack_create();
    linked_stack_push(stack, 1);
    linked_stack_push(stack, 2);
    linked_stack_push(stack, 3);
    
    ASSERT_EQ(3, linked_stack_pop(stack));
    ASSERT_EQ(2, linked_stack_pop(stack));
    ASSERT_EQ(1, linked_stack_pop(stack));
    ASSERT_EQ(0, linked_stack_pop(stack));
    
    linked_stack_destroy(stack);
    return 1;
}

int test_large_stack() {
    struct linked_stack *stack = linked_stack_create();
    
    for (int i = 1; i <= 100; i++) {
        linked_stack_push(stack, i);
    }
    
    for (int i = 100; i >= 1; i--) {
        ASSERT_EQ(i, linked_stack_pop(stack));
    }
    
    linked_stack_destroy(stack);
    return 1;
}

int main() {
    RUN_TEST(test_create_destroy);
    RUN_TEST(test_push_pop);
    RUN_TEST(test_lifo_order);
    RUN_TEST(test_pop_empty_stack);
    RUN_TEST(test_multiple_operations);
    RUN_TEST(test_example_sequence);
    RUN_TEST(test_large_stack);
    
    TEST_MAIN_END();
}