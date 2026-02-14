#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "rawqueue.h"
#include "queue.h"
#include "arrayqueue.h"

/*
int main(){
    rawqueue *q = rawqueue_create();
    
    rawqueue_enqueue(q, 14);
    rawqueue_enqueue(q, 22);
    rawqueue_enqueue(q, 53);
    rawqueue_enqueue(q, 57);
    rawqueue_enqueue(q, 78);
    rawqueue_enqueue(q, 62);
    rawqueue_enqueue(q, 32);
    
    rawqueue_print(q);
    
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    
    rawqueue_enqueue(q, 75);
    rawqueue_enqueue(q, 85);
    rawqueue_enqueue(q, 95);
    rawqueue_enqueue(q, 75);
    rawqueue_enqueue(q, 85);
    rawqueue_enqueue(q, 95);
    
    printf("Empty? %d\n", rawqueue_empty(q));
    
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    printf("%d\n", rawqueue_dequeue(q));
    
    printf("Empty? %d\n", rawqueue_empty(q));
    
    rawqueue_free(q);
}
*/

int main(){
    arrayqueue *q = arrayqueue_create();
    
    arrayqueue_enqueue(q, 14);
    arrayqueue_enqueue(q, 22);
    arrayqueue_enqueue(q, 53);
    arrayqueue_enqueue(q, 57);
    arrayqueue_enqueue(q, 78);
    arrayqueue_enqueue(q, 62);
    arrayqueue_enqueue(q, 32);
    
    arrayqueue_print(q);
    
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    
    arrayqueue_print(q);
    
    arrayqueue_enqueue(q, 75);
    arrayqueue_enqueue(q, 85);
    arrayqueue_enqueue(q, 95);
    arrayqueue_enqueue(q, 75);
    arrayqueue_enqueue(q, 85);
    arrayqueue_enqueue(q, 95);
    
    arrayqueue_print(q);
    
    printf("Empty? %d\n", arrayqueue_empty(q));
    
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    printf("%d\n", arrayqueue_dequeue(q));
    
    arrayqueue_print(q);
    
    printf("Empty? %d\n", arrayqueue_empty(q));
    
    arrayqueue_free(q);
}