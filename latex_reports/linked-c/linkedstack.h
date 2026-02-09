typedef struct linked_stack_cell {
    int value;
    struct cell *tail;
} linked_stack_cell;

typedef struct linked_stack {
    cell *first;
} linked_stack;

linked_stack *linked_stack_create();
void linked_stack_free(linked_stack *lnk);
void linked_stack_print(linked_stack *lnk);
void linked_stack_push(linked_stack *lnk, int item);
int linked_stack_pop(linked_stack *lnk);
int linked_stack_peek(linked_stack *lnk);