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
        exit(1); // or return NULL to propagate the error
    }
    new_cell->head = item;
    new_cell->tail = tl;
    return new_cell;
}

void linked_cell_destroy(struct linked_cell *c) {
    free(c);
}

struct linked_list_raw {
    struct linked_cell *first;
    int size;
};

struct linked_list_raw *create_linked_list_raw() {
    struct linked_list_raw *l = (struct linked_list_raw *) malloc(sizeof(struct linked_list_raw));
    if (l == NULL) {
        fprintf(stderr, "Memory allocation failed while create_linked_list_raw()!\n");
        exit(1);
    }
    l->first = NULL;
    l->size = 0;
    return l;
}

void linked_list_raw_add(struct linked_list_raw *lnk , int key) {
    lnk->size += 1;
    lnk->first = linked_cell_create (key, lnk->first);
}

void linked_list_raw_append(struct linked_list_raw *a, struct linked_list_raw *b) {
    struct linked_cell *nxt = a->first;
    struct linked_cell *prv = NULL;
    while (nxt != NULL) {
        prv = nxt;
        nxt = nxt->tail;
    }
    if (prv == NULL) {
        a->first = b->first;
    }
    else {
        prv->tail = b->first;
    }
    a->size += b->size;
    b->first = NULL;
    b->size = 0;
}

void linked_list_raw_delete(struct linked_list_raw *lnk, int key) {
    struct linked_cell *nxt = lnk->first;
    struct linked_cell *prev = NULL;
    while (nxt != NULL) {
        if (nxt->head == key) {
            lnk->size -= 1;
            if(prev == NULL) {
                lnk->first = nxt->tail;
            }
            else {
                prev->tail = nxt->tail;
            }
            lnk->size -= 1;
            linked_cell_destroy(nxt);
            break;
        }
        prev = nxt;
        nxt = nxt->tail;
    }
}

void linked_list_reverse(struct linked_list_raw *lnk) {
    struct linked_cell *nxt = lnk->first;
    struct linked_cell *last = NULL;
    while ( nxt != NULL ) {
        struct linked_cell *tmp = nxt;
        nxt = tmp->tail;
        tmp->tail = last;
        last = tmp;
    }
    lnk->first = last;
}

void linked_list_print(struct linked_list_raw *l) {
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

bool linked_list_search (struct linked_list_raw *lst , int key) {
    struct linked_cell *nxt = lst -> first;
    while (nxt != NULL) {
        if (nxt->head == key)
            return true;
        nxt = nxt->tail ;
    }
    return false;
}

void linked_list_destroy(struct linked_list_raw *l) {
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

// Merge sort

struct linked_cell *lsplit(struct linked_cell *a, int n) {
    for(int i = 0; i < n-1; i++) {
        a = a->tail;
    }
    struct linked_cell *b = a->tail;
    a->tail = NULL;
    return b;
}

static struct linked_cell *lmerge(struct linked_cell *a, struct linked_cell *b){
    if (a == NULL){
        return b;
    }
    if (b == NULL){
        return a;
    }
    struct linked_cell *result = NULL;
    if (a->head <= b->head){
        result = a;
        a = a->tail;
    }
    else{
        result = b;
        b = b->tail;
    }
    struct linked_cell *result_pointer = result;
    while (a != NULL && b != NULL){
        if (a->head <= b->head){
            result_pointer->tail = a;
            a = a->tail;
        }
        else{
            result_pointer->tail = b;
            b = b->tail;
        }
        result_pointer = result_pointer->tail;
    }
    if (a != NULL){
        result_pointer->tail = a;
    }
    else{
        result_pointer->tail = b;
    }
    return result;
}

struct linked_cell *lsort (struct linked_cell *a, int n) {
    if( n < 2) return a;
    int na = n /2;
    int nb = n - na;
    struct linked_cell *b = lsplit(a, na);
    struct linked_cell *sorted_a = lsort (a, na);
    struct linked_cell *sorted_b = lsort (b, nb);
    return lmerge (sorted_a, sorted_b);
}

void linked_list_sort (struct linked_list_raw *lnkd) {
    lnkd->first = lsort(lnkd->first, lnkd->size);
}