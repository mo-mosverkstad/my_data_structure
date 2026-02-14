#include <stdbool.h>

typedef struct arrayqueue{
    int *array;
    unsigned int capacity;
    unsigned int first;
    unsigned int last;
} arrayqueue;

arrayqueue *arrayqueue_create();
void arrayqueue_free(arrayqueue *aq);
bool arrayqueue_empty(arrayqueue *aq);
void arrayqueue_enqueue(arrayqueue* aq, int v);
int arrayqueue_dequeue(arrayqueue *aq);
void arrayqueue_print(arrayqueue *aq);