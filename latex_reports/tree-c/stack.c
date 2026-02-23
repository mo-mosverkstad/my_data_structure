/**
 * Dynamic array-based stack implementation for tree nodes.
 * Automatically grows when capacity is reached using realloc.
 */

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Creates a new empty stack with initial capacity of 16.
 * Exits the program if allocation fails.
 * @return Pointer to the newly created stack
 */
stack *stack_create(void) {
    // Allocate the stack control structure
    stack *stk = (stack *) malloc(sizeof(stack));
    if (stk == NULL) {
        perror("Malloc stack control block failure");
        exit(EXIT_FAILURE); // Fatal error
    }
    
    // Initialize stack properties
    stk->capacity = 16; // Start with 16 elements
    stk->top = 0;       // Empty stack (top points to next free slot)
    
    // Allocate the array to hold node pointers
    stk->elements = (node **) malloc(stk->capacity * sizeof(node *));
    if (stk->elements == NULL) {
        perror("Malloc array elements failure");
        exit(EXIT_FAILURE); // Fatal error
    }
    return stk;
}

/**
 * Frees all memory associated with the stack.
 * Does not free the nodes themselves, only the stack structure.
 * @param stk Pointer to the stack to free
 */
void stack_free(stack *stk) {
    if (stk != NULL) {
        free(stk->elements); // Free the array
        free(stk);           // Free the control structure
    }
}

/**
 * Pushes a node pointer onto the stack.
 * Automatically doubles capacity if stack is full.
 * @param stk Pointer to the stack
 * @param nd Node pointer to push
 */
void stack_push(stack *stk, node *nd) {
    // Check if stack is at capacity and needs to grow
    if (stk->top == stk->capacity) {
        // Double the capacity
        size_t new_capacity = stk->capacity * 2;
        
        // Reallocate array with new capacity
        node **new_elements = (node **) realloc(stk->elements, new_capacity * sizeof(node *));
        if (new_elements == NULL) {
            perror("Stack growth by realloc failure");
            exit(EXIT_FAILURE); // Fatal error
        }
        
        // Update stack with new array and capacity
        stk->elements = new_elements;
        stk->capacity = new_capacity;
    }
    
    // Push element onto stack and increment top
    stk->elements[stk->top++] = nd;
}

/**
 * Checks if the stack is empty.
 * @param stk Pointer to the stack
 * @return true if empty, false otherwise
 */
bool stack_empty(const stack *stk) {
    return stk->top == 0; // Empty when top is at position 0
}

/**
 * Pops and returns the top node pointer from the stack.
 * @param stk Pointer to the stack
 * @return Node pointer from top, or NULL if stack is empty
 */
node *stack_pop(stack *stk) {
    if (stk->top == 0) return NULL; // Stack is empty
    
    // Decrement top (moves to last element) and return it
    return stk->elements[--stk->top];
}
