#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "naive_heap1.h"
#include "naive_heap2.h"
#include "tree.h"
#include "tree_heap.h"

int main(){
    tree* h = construct_tree();
    tree_heap_enqueue(h, 10);
    tree_heap_enqueue(h, 8);
    tree_heap_enqueue(h, 22);
    tree_heap_enqueue(h, 77);
    tree_heap_enqueue(h, 58);
    tree_heap_enqueue(h, 99);
    tree_heap_enqueue(h, 121);
    tree_heap_enqueue(h, 33);
    tree_heap_enqueue(h, 47);
    tree_heap_enqueue(h, 7);
    
    int result = 0;
    while (tree_heap_dequeue(h, &result)){
        printf("%d ", result);
    }
    printf("\n");
    
    free_tree(h);
}

