#include <stdio.h>
#include <stdlib.h>

struct linked_cell {
    void *item ;
    struct linked_cell *next ;
};

struct linked_cell *linked_cell_create(const void *item, struct linked_cell *next) {
    struct linked_cell *new_node = (struct linked_cell *) malloc(sizeof(struct linked_cell));
    new_node->item = (void *)item;
    new_node->next = next;
    return new_node;
}

void linked_cell_destroy(struct linked_cell *linked_cell) {
    free(linked_cell);
}

struct linked_queue {
    struct linked_cell *first;
    struct linked_cell *last;
};

struct linked_queue *linked_queue_create(){
    struct linked_queue *queue = (struct linked_queue *) malloc(sizeof(struct linked_queue));
    queue->first = NULL;
    queue->last = NULL;
    return queue;
}

void linked_queue_destroy(struct linked_queue *queue) {
    free(queue);
}

void linked_queue_enqueue(struct linked_queue *queue, const void *item) {
    struct linked_cell *new_node = linked_cell_create(item, NULL);
    if (queue->first == NULL){
        queue->first = new_node;
    }
    if (queue->last != NULL)
        queue->last->next = new_node;
    queue->last = new_node;
}

const void *linked_queue_dequeue(struct linked_queue *queue){
    void *item = NULL;
    if (queue->first != NULL){
        struct linked_cell *linked_cell = queue->first;
        item = linked_cell->item;
        queue->first = linked_cell->next;
        linked_cell_destroy(linked_cell);
    }
    return item;
}