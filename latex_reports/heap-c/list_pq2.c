#include <stdlib.h>
#include <stdbool.h>

// List-based priority queue implementation 2
// Strategy: Slow enqueue O(n), fast dequeue O(1)
// Elements stored in sorted order (descending: largest to smallest)
// Minimum element always at the end for O(1) removal

typedef struct list_pq2{
    int *arr;           // Dynamic array to store elements in sorted order
    unsigned int top;   // Number of elements currently in queue
    unsigned int cap;   // Maximum capacity
} list_pq2;

// return a valid pointer adress if success
// return NULL if failed operation -> detected caller
list_pq2 *list_pq2_create(unsigned int cap){
    // Allocate memory for the priority queue structure
    list_pq2 *nh = (list_pq2 *) malloc(sizeof(list_pq2));
    if (!nh) return NULL;
    
    // Allocate memory for the array
    int *arr = (int *) malloc(cap * sizeof(int));
    if (!arr){
        free(nh);  // Clean up if array allocation fails
        return NULL;
    }
    nh->arr = arr;
    nh->top = 0;   // Start with empty queue
    nh->cap = cap;
    return nh;
}

void list_pq2_free(list_pq2 *nh){
    if (!nh) return;
    if (nh->arr){
        free(nh->arr);  // Free the array first
    }
    free(nh);  // Then free the structure
}

// Enqueue: O(n) - insert in sorted position to maintain order
// Array kept sorted in descending order (largest first, smallest last)
bool list_pq2_enqueue(list_pq2 *nh, int val){    
    if (!nh || nh->top >= nh->cap) return false;  // Check if full
    
    // Find insertion position by shifting larger elements right
    int i = (int) nh->top-1;
    while (i >= 0 && nh->arr[i] < val){
        nh->arr[i+1] = nh->arr[i];  // Shift element right
        i--;
    }
    nh->arr[i+1] = val;  // Insert at correct sorted position
    nh->top++;           // Increment size
    return true;
}

// Dequeue: O(1) - minimum is always at the end
// Simply decrement size to remove last element
bool list_pq2_dequeue(list_pq2 *nh, int *res_ptr){
    if (!nh || nh->top == 0 || !res_ptr) return false;  // Check if empty
    *res_ptr = nh->arr[--nh->top];  // Return and remove last element (minimum)
    return true;
}
