#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 16

struct array_queue {
    void **items;
    int size;
    int first;
    int last;
};

struct array_queue *array_queue_create() {
    struct array_queue *queue = (struct array_queue *) malloc(sizeof(struct array_queue));
    queue->items = (void **) malloc (sizeof(void *)* SIZE);
    queue->first = 0;
    queue->last = 0;
    queue->size = SIZE;
    return queue;
}

void array_queue_destroy(struct array_queue *queue) {
    free(queue->items);
    free(queue);
}


bool array_queue_is_empty(struct array_queue *queue) {
    return (queue->first == queue->last);
}

bool array_queue_is_full(struct array_queue *queue) {
    return (queue->first != queue->last && queue->last % queue->size == queue->first % queue->size);
}

void array_queue_enqueue(struct array_queue *queue, void *item) {
    if (array_queue_is_full(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue->items[queue->last % queue->size] = item;
    queue->last = queue->last + 1;
}

static void *array_queue_dequeue(struct array_queue *queue) {
    if (array_queue_is_empty(queue)) {
        printf("Queue is empty\n");
        return NULL;
    }
    // Get the item first, then increment the `first` pointer
    void *item = queue->items[queue->first % queue->size];
    queue->first = queue->first + 1;
    return item;
}


int main() {
    struct array_queue *queue = array_queue_create();
    int i;
    for (i = 0; i < 20; i++) {
        array_queue_enqueue(queue, &i);
    }
    for (i = 0; i < 20; i++) {
        int *value_pointer = (int*) array_queue_dequeue(queue);
        if (value_pointer == NULL) {
            printf("NULL\n");
        }
        else{
            printf("%d\n", *value_pointer);
        }
    }

    array_queue_destroy(queue);
    return 0;
}
