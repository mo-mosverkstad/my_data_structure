#include <stdbool.h>

struct linked_list_raw;
struct linked_list_raw *create_linked_list_raw();
void linked_list_raw_add(struct linked_list_raw *lnk , int key);
void linked_list_raw_append(struct linked_list_raw *a, struct linked_list_raw *b);
void linked_list_raw_delete(struct linked_list_raw *lnk, int key);
void linked_list_reverse(struct linked_list_raw *lnk);
void linked_list_print(struct linked_list_raw *l);
bool linked_list_search (struct linked_list_raw *lst , int key);
void linked_list_destroy(struct linked_list_raw *l);
void linked_list_sort (struct linked_list_raw *lnkd);