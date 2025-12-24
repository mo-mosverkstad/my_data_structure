struct linked_stack;
struct linked_stack *linked_stack_create();
void linked_stack_push(struct linked_stack *s, int item);
int linked_stack_pop(struct linked_stack *s);
void linked_stack_destroy(struct linked_stack *s);