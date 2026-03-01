#pragma once

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
tree *construct_tree();
void free_tree(tree *tr);