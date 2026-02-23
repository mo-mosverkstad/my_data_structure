/**
 * Circular array-based queue implementation for tree nodes.
 * Uses modulo arithmetic to wrap around the array.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

#define DEFAULT_CAPACITY 4

/**
 * Circular queue structure.
 * first: index of the front element
 * last: index where the next element will be inserted
 * Queue is empty when first == last
 * Queue is full when (last + 1) % capacity == first
 */
typedef struct arrayqueue{
    node **array;        // Array of node pointers
    unsigned int capacity; // Total capacity of the array
    unsigned int first;    // Index of front element
    unsigned int last;     // Index for next insertion
} arrayqueue;

/**
 * Creates a new empty queue with default capacity.
 * @return Pointer to the new queue, or NULL if allocation fails
 */
arrayqueue *arrayqueue_create(){
    // Allocate the queue control structure
    arrayqueue *aq = (arrayqueue*) malloc(sizeof(arrayqueue));
    if (aq == NULL) return NULL; // malloc failed
    
    // Allocate the array to hold node pointers
    node **array = (node**) malloc(sizeof(node *) * DEFAULT_CAPACITY);
    if (array == NULL) {
        free(aq); // Array allocation failed, clean up queue structure
        return NULL;
    }
    
    // Initialize queue properties
    aq->array = array;
    aq->capacity = DEFAULT_CAPACITY;
    aq->first = 0;  // Front of queue (where we dequeue from)
    aq->last = 0;   // Back of queue (where we enqueue to)
    return aq;
}

/**
 * Frees all memory associated with the queue.
 * Does not free the nodes themselves, only the queue structure.
 * @param aq Pointer to the queue to free
 */
void arrayqueue_free(arrayqueue *aq){
    if (aq == NULL) return; // Nothing to free
    free(aq->array);        // Free the array
    free(aq);               // Free the control structure
}

/**
 * Checks if the queue is empty.
 * @param aq Pointer to the queue
 * @return true if empty or NULL, false otherwise
 */
bool arrayqueue_empty(arrayqueue *aq){
    if (aq == NULL) return true; // NULL queue is considered empty
    // In circular queue: empty when first == last
    return aq->first == aq->last;
}

/**
 * Adds a node pointer to the back of the queue.
 * Automatically resizes the queue if full.
 * @param aq Pointer to the queue
 * @param v Node pointer to enqueue
 */
void arrayqueue_enqueue(arrayqueue* aq, node *v){
    if (aq == NULL) return; // Invalid queue
    
    // Check if queue is full using circular buffer full condition
    // Full when: next position of last would equal first
    if ((aq->last + 1) % aq->capacity == aq->first){
        // Queue is full, need to resize
        unsigned int new_capacity = aq->capacity * 2; // Double the size
        
        // Allocate new larger array
        node **new_array = (node **) malloc(sizeof(node *) * new_capacity);
        if (new_array == NULL) return; // Resize failed, silently fail
        
        // Copy elements from old array to new array in order
        // This "unwraps" the circular buffer into a linear array
        unsigned int old_index = aq->first; // Start from front
        unsigned int new_index = 0;         // Place at beginning of new array
        while (old_index != aq->last){
            new_array[new_index] = aq->array[old_index];
            old_index = (old_index + 1) % aq->capacity; // Wrap around old array
            new_index++;
        }
        
        // Replace old array with new one
        free(aq->array);
        aq->capacity = new_capacity;
        aq->first = 0;        // Reset to start of new array
        aq->last = new_index; // Points to next free slot
        aq->array = new_array;
    }
    
    // Insert element at last position
    aq->array[aq->last] = v;
    // Advance last pointer with wraparound using modulo
    aq->last = (aq->last + 1) % aq->capacity;
}

/**
 * Removes and returns the node pointer from the front of the queue.
 * @param aq Pointer to the queue
 * @return Node pointer from front, or NULL if queue is empty
 */
node *arrayqueue_dequeue(arrayqueue *aq){
    if (aq == NULL) return NULL; // Invalid queue
    
    // Check if queue has elements
    if (!arrayqueue_empty(aq)){
        // Get element at front of queue
        node *result = aq->array[aq->first];
        // Advance first pointer with wraparound using modulo
        aq->first = (aq->first + 1) % aq->capacity;
        return result;
    }
    return NULL; // Queue is empty
}

/**
 * Prints the internal state of the queue for debugging.
 * Shows capacity, indices, and all array elements (including empty slots).
 * @param aq Pointer to the queue
 */
void arrayqueue_print(arrayqueue *aq){
    if (aq == NULL) return; // Nothing to print
    
    // Print queue metadata
    printf("(CAPACITY=%d, FIRST=%d, LAST=%d)[", aq->capacity, aq->first, aq->last);
    
    // Print all array slots (not just occupied ones)
    if (aq->capacity > 0){
        // Print all but last element with comma
        for (unsigned int i = 0; i < aq->capacity-1; i++){
            printf("%p, ", aq->array[i]);
        }
        // Print last element without comma
        printf("%p", aq->array[aq->capacity-1]);
    }
    printf("]\n");
}