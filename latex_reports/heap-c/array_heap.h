#include <stdbool.h>

typedef struct array_heap{
    int* array;
    unsigned int depth;   // capacity
    unsigned int size;    // current number of elements
} array_heap;

array_heap* create_array_heap(unsigned int depth);
void free_array_heap(array_heap* heap);
bool array_heap_enqueue(array_heap* heap, int value);
bool array_heap_dequeue(array_heap* heap, int* res_ptr);