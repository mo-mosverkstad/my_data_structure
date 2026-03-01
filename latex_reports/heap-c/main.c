#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "naive_heap1.h"
#include "naive_heap2.h"
#include "bst_heap.h"
#include "tree_heap.h"
#include "array_heap.h"

int main(){
    array_heap* h = create_array_heap(15);
    array_heap_enqueue(h, 22);
    array_heap_enqueue(h, 8);
    array_heap_enqueue(h, 10);
    array_heap_enqueue(h, 77);
    array_heap_enqueue(h, 58);
    array_heap_enqueue(h, 99);
    array_heap_enqueue(h, 121);
    array_heap_enqueue(h, 33);
    array_heap_enqueue(h, 47);
    array_heap_enqueue(h, 7);
    
    int result = 0;
    while (array_heap_dequeue(h, &result)){
        printf("%d ", result);
    }
    printf("\n");
    
    free_array_heap(h);
}