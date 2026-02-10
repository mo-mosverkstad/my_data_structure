#include <stdlib.h>
#include <stdio.h>

typedef struct linked_stack_cell {
    int value;
    struct linked_stack_cell *tail;
} linked_stack_cell;

typedef struct linked_stack {
    linked_stack_cell *first;
} linked_stack;

linked_stack *linked_stack_create() {
    linked_stack *new = (linked_stack*) malloc(sizeof(linked_stack));
    if (new == NULL) return NULL;
    new->first = NULL;
    return new;
}

void linked_stack_free(linked_stack *lnk) {
    linked_stack_cell *nxt = lnk->first;
    while (nxt != NULL) {
        linked_stack_cell *tmp = nxt->tail;
        free(nxt);
        nxt = tmp;
    }
    free(lnk);
}

void linked_stack_print(linked_stack *lnk){
    printf("linked_stack[");
    linked_stack_cell *nxt = lnk->first;
    if (nxt != NULL){
        while (nxt->tail != NULL){
            printf("%d, ", nxt->value);
            nxt = nxt->tail;
        }
        printf("%d", nxt->value);
    }
    printf("]\n");
}

// add the item as the first cell in the list
void linked_stack_push(linked_stack *lnk, int item) {
    linked_stack_cell *new = (linked_stack_cell*) malloc(sizeof(linked_stack_cell));
    if (new == NULL) return;
    new->value = item;
    new->tail = lnk->first;
    lnk->first = new;
}

int linked_stack_pop(linked_stack *lnk) {
    if (lnk->first == NULL) {
        return 0;
    }
    linked_stack_cell *first_cell = lnk->first;
    int value = first_cell->value;
    lnk->first = lnk->first->tail;
    free(first_cell);
    return value;
}

int linked_stack_peek(linked_stack *lnk){
    if (lnk->first == NULL){
        return 0;
    }
    return lnk->first->value;
}