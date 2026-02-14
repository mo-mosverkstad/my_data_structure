#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "node.h"

typedef struct queue {
    node *first;
    node *last;
} queue;

queue *queue_create() {
    queue *q = (queue*)malloc(sizeof(queue));
    q->first = NULL;
    q->last = NULL;
    return q;
}

void queue_free(queue *q){
    node *nxt = q->first;
    while (nxt != NULL){
        node *nd = nxt;
        nxt = nxt->next;
        free(nd);
    }
    free(q);
}

bool queue_empty(queue *q) {
    return q->first == NULL;
}

void queue_enqueue(queue* q, int v) {
    node *nd = (node*) malloc(sizeof(node));
    nd->value = v;
    nd->next = NULL;
    if (q->first == NULL) {
        q->first = nd;
        q->last = nd;
    } else {
        q->last->next = nd;
        q->last = nd;
    }
}

int queue_dequeue(queue *q) {
    int res = 0;
    if (q->first != NULL) {
        node *nd = q->first;
        res = nd->value;
        q->first = nd->next;
        free(nd);
    }
    return res;
}

void queue_print(queue *q){
    printf("[");
    node *nd = q->first;
    if (nd != NULL){
        while (nd->next != NULL){
            printf("%d, ", nd->value);
            nd = nd->next;
        }
        printf("%d", nd->value);
    }
    printf("]\n");
}