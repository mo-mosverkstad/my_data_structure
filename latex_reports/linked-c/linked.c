#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct cell {
    int value;
    struct cell *tail;
} cell;

typedef struct linked {
    cell *first;
} linked;

linked *linked_create() {
    linked *new = (linked*)malloc(sizeof(linked));
    new->first = NULL;
    return new;
}
void linked_free(linked *lnk) {
    cell *nxt = lnk->first;
    while (nxt != NULL) {
        cell *tmp = nxt->tail;
        free(nxt);
        nxt = tmp;
    }
    free(lnk);
}

void linked_print(linked *lnk){
    printf("[");
    cell *nxt = lnk->first;
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
void linked_add(linked *lnk, int item) {
    cell *new = (cell*) malloc(sizeof(cell));
    new->value = item;
    new->tail = lnk->first;
    
    lnk->first = new;
}

// add the item as the last cell in the list (optional)
void linked_add_last(linked *lnk, int item) {
    cell *new = (cell*) malloc(sizeof(cell));
    new->value = item;
    new->tail = NULL;
    
    if (lnk->first == NULL){
        lnk->first = new;
    }
    else{
        cell *nxt = lnk->first;
        while (nxt->tail != NULL){
            nxt = nxt->tail;
        }
        nxt->tail = new;
    }
}

unsigned int linked_length(linked *lnk){
    unsigned int length = 0;
    cell* nxt = lnk->first;
    while (nxt != NULL){
        nxt = nxt->tail;
        length++;
    }
    return length;
}

/*
// add the item in arbitrary position in the list
void linked_insert(linked *lnk, unsigned int index, int item){
    cell *new = (cell*) malloc(sizeof(cell));
    new->value = item;
    new->tail = NULL;
    
    
}
*/


// return true or false depending on if the item can be found in the list
bool linked_find(linked *lnk, int item){
    cell *nxt = lnk->first;
    while (nxt != NULL && nxt->value != item){
        nxt = nxt->tail;
    }
    return nxt != NULL;
}


// remove the item if it exists in the list (and also free the cell)
void linked_remove(linked *lnk, int item){
    cell *nxt = lnk->first;
    if (nxt == NULL) return;
    if (nxt->value == item){
        cell *after = nxt->tail;
        free(nxt);
        lnk->first = after;
    }
    else{
        while (nxt->tail != NULL && nxt->tail->value != item){
            nxt = nxt->tail;
        }
        if (nxt->tail != NULL){
            cell *after = nxt->tail->tail;
            free(nxt->tail);
            nxt->tail = after;
        }
    }
}


void linked_append(linked *a, linked *b) {
    cell *nxt = a->first;
    cell *prv = NULL;
    while(nxt != NULL) {
        prv = nxt;
        nxt = nxt->tail;
    }
    if (prv == NULL){
        a->first = b->first;
    }
    else{
        prv->tail = b->first;
    }
    b->first = NULL;
}