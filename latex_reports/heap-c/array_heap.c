#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct array_heap{
    int* array;
    unsigned int depth;   // capacity
    unsigned int size;    // current number of elements
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

static void bubble_up(array_heap* heap, unsigned int index){
    int child_val = heap->array[index];
    unsigned int parent = index == 0 ? 0 : (index - 1) / 2;
    int parent_val = heap->array[parent];
    while (index > 0 && child_val < parent_val) {
        heap->array[index] = parent_val;
        heap->array[parent] = child_val;
        index = parent;

        child_val = heap->array[index];
        parent = index == 0 ? 0 : (index - 1) / 2;
        parent_val = heap->array[parent];
    }
}

bool array_heap_enqueue(array_heap* heap, int value){
    if (heap->size >= heap->depth)
        return false; // full

    heap->array[heap->size] = value;
    bubble_up(heap, heap->size);
    heap->size++;
    return true;
}

static void sink_down(array_heap* heap, unsigned int index){
    while (1) {
        unsigned int left = 2 * index + 1;
        unsigned int right = 2 * index + 2;
        unsigned int smallest = index;
        if (left < heap->size && heap->array[left] < heap->array[smallest])
            smallest = left;
        if (right < heap->size && heap->array[right] < heap->array[smallest])
            smallest = right;

        if (smallest == index) break;
        int tmp = heap->array[index];
        heap->array[index] = heap->array[smallest];
        heap->array[smallest] = tmp;
        index = smallest;
    }
}

bool array_heap_dequeue(array_heap* heap, int* res_ptr){
    if (heap->size == 0)
        return false; // empty

    *res_ptr = heap->array[0];

    heap->size--;
    heap->array[0] = heap->array[heap->size];
    sink_down(heap, 0);

    return true;
}