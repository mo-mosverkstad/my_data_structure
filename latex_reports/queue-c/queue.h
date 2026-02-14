#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "node.h"

typedef struct queue {
    node *first;
    node *last;
} queue;

queue *queue_create();
void queue_free(queue *q);
bool queue_empty(queue *q);
void queue_enqueue(queue* q, int v);
int queue_dequeue(queue *q);
void queue_print(queue *q);