#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

typedef struct node {
    int value;
    struct node *right;
    struct node *left;
} node;

typedef struct tree {
    node *root;
} tree;

node *construct_node(int val);
void free_node(node *nd);
tree *construct_tree(void);
void free_tree(tree *tr);
void add(tree *tr, int value);
void recursive_add(tree *tr, int value);
bool recursive_lookup(tree *tr, int value);
bool tree_lookup_iterative(const tree *tr, int value);
void print_tree(tree *tr);
void tree_print_inorder_stack(const tree *tr);
void breadth_first_print(const tree *tr);
void tree_delete(tree *tr, int k);

#endif
