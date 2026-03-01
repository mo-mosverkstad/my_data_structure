#pragma once
#include <stdbool.h>

typedef struct bst_node bst_node;
typedef struct bst_tree bst_tree;

bst_tree *construct_bst_tree(void);
void free_bst_tree(bst_tree *tr);
bool bst_heap_enqueue(bst_tree *tr, int value);
bool bst_heap_dequeue(bst_tree *tr, int* res_ptr);
void bst_heap_print(bst_tree *tr);
