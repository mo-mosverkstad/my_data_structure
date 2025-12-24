#include <stdbool.h>

struct linked_list;
struct linked_list *linked_list_create();
void linked_list_add(struct linked_list *l, int x);
void linked_list_add_first(struct linked_list *l, int x);
void linked_list_print_out(struct linked_list *l);
void linked_list_append(struct linked_list *a, struct linked_list *b);
bool linked_list_search(struct linked_list *lst , int key);
void linked_list_destroy(struct linked_list *l);
