#include <stdbool.h>

typedef struct cell {
    int value;
    struct cell *tail;
} cell;

typedef struct linked {
    cell *first;
} linked;

linked *linked_create();
void linked_free(linked *lnk);
void linked_print(linked *lnk);
void linked_add(linked *lnk, int item);
void linked_add_last(linked *lnk, int item);
unsigned int linked_length(linked *lnk);
bool linked_find(linked *lnk, int item);
void linked_remove(linked *lnk, int item);
void linked_append(linked *a, linked *b);