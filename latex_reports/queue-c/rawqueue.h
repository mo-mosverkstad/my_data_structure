#include <stdbool.h>

#include "node.h"

typedef struct rawqueue {
    node *first;
} rawqueue;

rawqueue *rawqueue_create();
void rawqueue_free(rawqueue *q);
bool rawqueue_empty(rawqueue *q);
void rawqueue_enqueue(rawqueue* q, int v);
int rawqueue_dequeue(rawqueue *q);
void rawqueue_print(rawqueue *q);