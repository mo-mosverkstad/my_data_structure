#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct linked_cell {
    int head;
    struct linked_cell *tail;
};

struct linked_cell *linked_cell_create(int item, struct linked_cell *tl) {
    struct linked_cell *new_cell = (struct linked_cell *) malloc(sizeof(struct linked_cell));
    if (new_cell == NULL) {
        fprintf(stderr, "Memory allocation failed while linked_cell_create(%zu, ...)!\n", item);
        exit(1);
    }
    new_cell->head = item;
    new_cell->tail = tl;
    return new_cell;
}

void linked_cell_destroy(struct linked_cell *c) {
    free(c);
}

struct linked_list {
    struct linked_cell *first;
    struct linked_cell *last;
};

struct linked_list *linked_list_create() {
    struct linked_list *l = (struct linked_list *) malloc(sizeof(struct linked_list));
    if (l == NULL) {
        fprintf(stderr, "Memory allocation failed while linked_list_create()!\n");
        exit(1); // or return NULL to propagate the error
    }
    l->first = NULL;
    l->last = NULL;
    return l;
}

void linked_list_add(struct linked_list *l, int x){
    struct linked_cell *new_cell = linked_cell_create(x, NULL);
    if (l->first == NULL) {
        l->first = new_cell;
        l->last = new_cell;
    }
    else{
        l->last->tail = new_cell;
        l->last = new_cell;
    }
}

void linked_list_add_first(struct linked_list *l, int x) {
    struct linked_cell *new_cell = linked_cell_create(x, l->first);
    l->first = new_cell;
    if (l->last == NULL) {
        l->last = new_cell;
    }
}

void linked_list_print_out(struct linked_list *l) {
    printf("[");
    struct linked_cell *nxt = l->first;
    if (nxt != NULL){
        while (nxt->tail != NULL) {
            printf("%d, ", nxt->head);
            nxt = nxt->tail;
        }
        printf("%d", nxt->head);
    }
    printf("]");
}

void linked_list_append(struct linked_list *a, struct linked_list *b){
    if (a->first == NULL){
        a->first = b->first;
    }
    else{
        a->last->tail = b->first;
    }
    a->last = b->last;
    b->first = NULL;
    b->last = NULL;
}

bool linked_list_search(struct linked_list *lst , int key) {
    struct linked_cell *nxt = lst->first;
    while (nxt != NULL) {
        if (nxt->head == key)
            return true;
        nxt = nxt->tail ;
    }
    return false;
}

void linked_list_destroy(struct linked_list *l) {
    struct linked_cell *nxt = l->first;
    while (nxt != NULL) {
        struct linked_cell *temp = nxt;
        nxt = nxt->tail;
        linked_cell_destroy(temp);
    }
    l->first = NULL;
    free(l);
    l = NULL;
}