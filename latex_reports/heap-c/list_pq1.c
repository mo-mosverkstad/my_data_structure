#include <stdlib.h>
#include <stdbool.h>

// List-based priority queue implementation 1
// Strategy: Fast enqueue O(1), slow dequeue O(n)
// Elements stored in insertion order (unsorted)

typedef struct list_pq1{
    int *arr;           // Dynamic array to store elements
    unsigned int top;   // Number of elements currently in queue
    unsigned int cap;   // Maximum capacity
} list_pq1;

// return a valid pointer adress if success
// return NULL if failed operation -> detected caller
list_pq1 *list_pq1_create(unsigned int cap){
    // Allocate memory for the priority queue structure
    list_pq1 *nh = (list_pq1 *) malloc(sizeof(list_pq1));
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

void list_pq1_free(list_pq1 *nh){
    if (!nh) return;
    if (nh->arr){
        free(nh->arr);  // Free the array first
    }
    free(nh);  // Then free the structure
}

// Enqueue: O(1) - simply append to end of array
// No sorting or searching needed
bool list_pq1_enqueue(list_pq1 *nh, int val){
    if (!nh || nh->top >= nh->cap) return false;  // Check if full
    nh->arr[nh->top++] = val;  // Add element and increment size
    return true;
}

// Dequeue: O(n) - must find and remove minimum element
// Returns minimum value via res_ptr
bool list_pq1_dequeue(list_pq1 *nh, int *res_ptr){
    if (!nh || nh->top == 0 || !res_ptr) return false;  // Check if empty
    
    // Step 1: Linear search to find minimum element - O(n)
    unsigned int min_index = 0;
    int min = nh->arr[0];
    for (unsigned int i = 1; i < nh->top; i++){
        if (nh->arr[i] < min){
            min = nh->arr[i];
            min_index = i;  // Track position of minimum
        }
    }
    
    *res_ptr = min;  // Return the minimum value
    
    // Step 2: Shift all elements after minimum to the left - O(n)
    for (unsigned int i = min_index; i < nh->top - 1; i++){
        nh->arr[i] = nh->arr[i + 1];
    }
    nh->top--;  // Decrease size
    return true;
}
