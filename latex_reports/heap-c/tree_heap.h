#include "tree.h"
#include <stdbool.h>

bool tree_heap_enqueue(tree *tr, int value);
bool tree_heap_dequeue(tree *tr, int* res_ptr);
void tree_heap_print(tree *tr);