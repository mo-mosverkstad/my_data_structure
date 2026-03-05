#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Array-based binary min-heap implementation
// Uses implicit binary tree structure in array:
// - Parent of index i is at (i-1)/2
// - Left child of index i is at 2*i+1
// - Right child of index i is at 2*i+2
// Maintains min-heap property: parent <= children

typedef struct array_heap{
    int* array;           // Array storing heap elements
    unsigned int depth;   // Maximum capacity
    unsigned int size;    // Current number of elements
} array_heap;

array_heap* create_array_heap(unsigned int depth){
    array_heap* new_heap = malloc(sizeof(array_heap));
    if (!new_heap) return NULL;

    new_heap->array = malloc(depth * sizeof(int));
    if (!new_heap->array) {
        free(new_heap);
        return NULL;
    }

    new_heap->depth = depth;
    new_heap->size = 0;
    return new_heap;
}

void free_array_heap(array_heap* heap){
    if (!heap) return;
    free(heap->array);
    free(heap);
}

// Helper function
static inline void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Bubble up: Restore heap property after insertion
// Move element up the tree while it's smaller than parent
static void bubble_up(array_heap* heap, unsigned int index){
    int child_val = heap->array[index];
    unsigned int parent = index == 0 ? 0 : (index - 1) / 2;
    int parent_val = heap->array[parent];
    
    // Swap with parent while child is smaller (min-heap property)
    while (index > 0 && child_val < parent_val) {
        heap->array[index] = parent_val;  // Move parent down
        heap->array[parent] = child_val;  // Move child up
        index = parent;  // Move to parent position

        // Recalculate for next iteration
        child_val = heap->array[index];
        parent = index == 0 ? 0 : (index - 1) / 2;
        parent_val = heap->array[parent];
    }
}

// Enqueue: O(log n) - add element and bubble up
bool array_heap_enqueue(array_heap* heap, int value){
    if (heap->size >= heap->depth)
        return false; // Heap is full

    heap->array[heap->size] = value;  // Add at end of array
    bubble_up(heap, heap->size);      // Restore heap property
    heap->size++;                     // Increment size
    return true;
}

// Sink down: Restore heap property after removal
// Move element down the tree while it's larger than smallest child
static void sink_down(array_heap* heap, unsigned int index){
    while (1) {
        unsigned int left = 2 * index + 1;   // Left child index
        unsigned int right = 2 * index + 2;  // Right child index
        unsigned int smallest = index;
        
        // Find smallest among node and its children
        if (left < heap->size && heap->array[left] < heap->array[smallest])
            smallest = left;   // Left child is smaller
        if (right < heap->size && heap->array[right] < heap->array[smallest])
            smallest = right;  // Right child is smaller

        if (smallest == index) break;  // Heap property satisfied
        
        // Swap with smallest child
        int tmp = heap->array[index];
        heap->array[index] = heap->array[smallest];
        heap->array[smallest] = tmp;
        index = smallest;  // Move down to child position
    }
}

// Dequeue: O(log n) - remove minimum and sink down
bool array_heap_dequeue(array_heap* heap, int* res_ptr){
    if (heap->size == 0)
        return false; // Heap is empty

    *res_ptr = heap->array[0];  // Return minimum (root)

    heap->size--;  // Decrease size
    heap->array[0] = heap->array[heap->size];  // Move last element to root
    sink_down(heap, 0);                        // Restore heap property

    return true;
}

// Peek: Return minimum value without removing it - O(1)
// Simply returns first element since min-heap property guarantees array[0] is minimum
bool array_heap_peek(array_heap* heap, int* res_ptr){
    if (heap->size == 0)
        return false; // Heap is empty

    *res_ptr = heap->array[0];  // First element always contains minimum
    return true;
}