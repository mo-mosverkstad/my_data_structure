#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

struct heap *heap_create(int capacity){
    struct heap *h = (struct heap *)malloc(sizeof(struct heap));
    h->size = 0;
    h->capacity = capacity;
    h->arr = (int *) malloc(capacity * sizeof(int));
    return h;
}

void heap_destroy(struct heap *h){
    free(h->arr);
    free(h);
}

void heap_add(struct heap *h, int val){
    if(h->size == h->capacity){
        printf("Heap is full\n");
        return;
    }
    int i = h->size;
    h->arr[i] = val;
    int parent_index = (i - 1) / 2;
    while (i > 0 && h->arr[parent_index] > h->arr[i]){
        int temp = h->arr[parent_index];
        h->arr[parent_index] = h->arr[i];
        h->arr[i] = temp;
        i = parent_index;
        parent_index = (i - 1) / 2;
    }
    h->size++;
}

int heap_delete(struct heap *h){
    if(h->size == 0){
        return 0;
    }
    int value = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    int i = 0;
    int downfiltering = 1;
    while(downfiltering){
        int left_child_index = 2 * i + 1;
        int right_child_index = 2 * i + 2;
        int smallest = i;
        if(left_child_index < h->size && h->arr[left_child_index] < h->arr[smallest])
            smallest = left_child_index;
        if(right_child_index < h->size && h->arr[right_child_index] < h->arr[smallest])
            smallest = right_child_index;
        if(smallest == i){
            downfiltering = 0;
        }
        else{
            int temp = h->arr[i];
            h->arr[i] = h->arr[smallest];
            h->arr[smallest] = temp;
        }
        i = smallest;
    }

    return value;
}

void heap_print(struct heap *h){
    printf("[");
    if (h->size > 0){
        int last_index = h->size - 1;
        for(int i = 0; i < last_index; i++){
            printf("%d, ", h->arr[i]);
        }
        printf("%d", h->arr[last_index]);
    }
    printf("]\n");
}