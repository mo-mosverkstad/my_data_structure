#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    int size;              // number of nodes in subtree
    struct node *left;
    struct node *right;
} node;

typedef struct {
    node *root;
} heap;

node *create_node(int value);
void free_node(node *nd);
heap *create_heap();
void free_heap(heap* hp);

bool tree_heap_enqueue(heap *hp, int value);
bool tree_heap_dequeue(heap *hp, int *res_ptr);
int push(heap *hp, int incr);