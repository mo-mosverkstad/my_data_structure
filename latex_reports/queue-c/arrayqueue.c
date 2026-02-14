#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_CAPACITY 4

typedef struct arrayqueue{
    int *array;
    unsigned int capacity;
    unsigned int first;
    unsigned int last;
} arrayqueue;

arrayqueue *arrayqueue_create(){
    arrayqueue *aq = (arrayqueue*) malloc(sizeof(arrayqueue));
    int *array = (int*) malloc(sizeof(int) * DEFAULT_CAPACITY);
    aq->array = array;
    aq->capacity = DEFAULT_CAPACITY;
    aq->first = 0;
    aq->last = 0;
    return aq;
}

void arrayqueue_free(arrayqueue *aq){
    free(aq->array);
    free(aq);
}

bool arrayqueue_empty(arrayqueue *aq){
    return aq->first == aq->last;
}

void arrayqueue_enqueue(arrayqueue* aq, int v){
    if ((aq->last + 1) % aq->capacity == aq->first){
        // resize the array
        unsigned int new_capacity = aq->capacity * 2;
        int *new_array = (int*) malloc(sizeof(int) * new_capacity);
        unsigned int old_index = aq->first;
        unsigned int new_index = 0;
        while (old_index != aq->last){
            new_array[new_index] = aq->array[old_index];
            old_index = (old_index + 1) % aq->capacity;
            new_index++;
        }
        free(aq->array);
        aq->capacity = new_capacity;
        aq->first = 0;
        aq->last = new_index;
        aq->array = new_array;
    }
    aq->array[aq->last] = v;
    aq->last = (aq->last + 1) % aq->capacity;
}

int arrayqueue_dequeue(arrayqueue *aq){
    if (!arrayqueue_empty(aq)){
        int result = aq->array[aq->first];
        aq->first = (aq->first + 1) % aq->capacity;
        return result;
    }
    return 0;
}

void arrayqueue_print(arrayqueue *aq){
    printf("(CAPACITY=%d, FIRST=%d, LAST=%d)[", aq->capacity, aq->first, aq->last);
    if (aq->capacity > 0){
        for (unsigned int i = 0; i < aq->capacity-1; i++){
            printf("%d, ", aq->array[i]);
        }
        printf("%d", aq->array[aq->capacity-1]);
    }
    printf("]\n");
}