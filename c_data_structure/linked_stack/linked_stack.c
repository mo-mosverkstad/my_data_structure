#include <stdio.h>
#include <stdlib.h>

struct linked_cell {
    int head;
    struct linked_cell *tail;
};

struct linked_cell *linked_cell_create(int item, struct linked_cell *tl) {
    struct linked_cell *new_cell = (struct linked_cell *) malloc(sizeof(struct linked_cell));
    if (new_cell == NULL) {
        fprintf(stderr, "Memory allocation failed while linked_cell_create(%zu, ...)!\n", item);
        exit(1); // or return NULL to propagate the error
    }
    new_cell->head = item;
    new_cell->tail = tl;
    return new_cell;
}

struct linked_stack {
    struct linked_cell *top;
};

struct linked_stack *linked_stack_create() {
    struct linked_stack *new_stack = (struct linked_stack *) malloc(sizeof( struct linked_stack ));
    new_stack->top = NULL;
    return new_stack;
}

void linked_stack_push(struct linked_stack *s, int item){
    s->top = linked_cell_create(item, s->top);
}

int linked_stack_pop(struct linked_stack *s){
    struct linked_cell *result_cell = s->top;
    if (result_cell == NULL){
        return 0;
    }
    s->top = s->top->tail;
    int result = result_cell->head;
    free(result_cell);
    return result;
}

void linked_stack_destroy(struct linked_stack *s){
    while (s->top != NULL){
        int c = linked_stack_pop(s);
    }
    free(s);
}