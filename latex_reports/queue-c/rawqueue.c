#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "node.h"

typedef struct rawqueue {
    node *first;
} rawqueue;

rawqueue *rawqueue_create() {
    rawqueue *q = (rawqueue*)malloc(sizeof(rawqueue));
    q->first = NULL;
    return q;
}

void rawqueue_free(rawqueue *q){
    node *nxt = q->first;
    while (nxt != NULL){
        node *nd = nxt;
        nxt = nxt->next;
        free(nd);
    }
    free(q);
}

bool rawqueue_empty(rawqueue *q) {
    return q->first == NULL;
}

void rawqueue_enqueue(rawqueue* q, int v) {
    node *nd = (node*) malloc(sizeof(node));
    nd->value = v;
    nd->next = NULL;
    node *prv = NULL;
    node *nxt = q->first;
    while (nxt != NULL) {
        prv = nxt;
        nxt = nxt->next;
    }
    if (prv == NULL) {
        q->first = nd;
    } else {
        prv->next = nd;
    }
}

int rawqueue_dequeue(rawqueue *q) {
    int res = 0;
    if (q->first != NULL) {
        node *nd = q->first;
        res = nd->value;
        q->first = nd->next;
        free(nd);
    }
    return res;
}

void rawqueue_print(rawqueue *q){
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