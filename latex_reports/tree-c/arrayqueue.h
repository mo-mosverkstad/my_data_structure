#pragma once
#include <stdbool.h>
#include "tree.h"

typedef struct arrayqueue{
    node **array;
    unsigned int capacity;
    unsigned int first;
    unsigned int last;
} arrayqueue;

arrayqueue *arrayqueue_create();
void arrayqueue_free(arrayqueue *aq);
bool arrayqueue_empty(arrayqueue *aq);
void arrayqueue_enqueue(arrayqueue* aq, node *v);
node *arrayqueue_dequeue(arrayqueue *aq);
void arrayqueue_print(arrayqueue *aq);