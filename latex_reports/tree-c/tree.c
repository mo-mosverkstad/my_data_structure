#include "tree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

node *construct_node(int val) {
    node *nd = (node*) malloc(sizeof(node));
    nd->value = val;
    nd->left = NULL;
    nd->right = NULL;
    return nd;
}

void free_node(node *nd) {
    if (nd != NULL) {
        free_node(nd->left);
        free_node(nd->right);
        free(nd);
    }
}

tree *construct_tree(void) {
    tree *tr = (tree*) malloc(sizeof(tree));
    tr->root = NULL;
    return tr;
}

void free_tree(tree *tr) {
    if (tr != NULL){
        free_node(tr->root);
        free(tr);
    }
}

static node* add_node(node *nd, int value){
    if (nd == NULL){
        return construct_node(value);
    }
    if (value < nd->value){
        nd->left = add_node(nd->left, value);
    }
    else if (value > nd->value){
        nd->right = add_node(nd->right, value);
    }
    return nd;
}

void recursive_add(tree *tr, int value){
    tr->root = add_node(tr->root, value);
}

void add(tree *tr, int value){
    bool left = true;
    node* parent = NULL;
    node* nd = tr->root;
    
    while (nd != NULL){
        if (value < nd->value){
            parent = nd;
            nd = nd->left;
            left = true;
        }
        else if (value > nd->value){
            parent = nd;
            nd = nd->right;
            left = false;
        }
        else{
            return;
        }
    }
    
    node* new_node = construct_node(value);
    if (parent == NULL){
        tr->root = new_node;
    }
    else{
        if (left){
            parent->left = new_node;
        }
        else{
            parent->right = new_node;
        }        
    }
}

static bool lookup_node(node *nd, int value){
    if (nd == NULL) return false;
    if (value < nd->value) return lookup_node(nd->left, value);
    else if (value > nd->value) return lookup_node(nd->right, value);
    return true;
}

bool recursive_lookup(tree *tr, int value){
    return lookup_node(tr->root, value);
}

bool tree_lookup_iterative(const tree *tr, int value) {
    const node *nd = tr->root;
    while (nd != NULL) {
        if (value == nd->value) return true;
        nd = (value < nd->value) ? nd->left : nd->right;
    }
    return false;
}

static void print(node *nd) {
    if (nd != NULL) {
        print(nd->left);
        printf("%d ", nd->value);
        print(nd->right);
    }
}

void print_tree(tree *tr) {
    if (tr->root != NULL)
        print(tr->root);
    printf("\n");
}

void tree_print_inorder_stack(const tree *tr) {
    stack *stk = stack_create();
    node *nd = tr->root;

    while (nd != NULL) {
        stack_push(stk, nd);
        nd = nd->left;
    }

    while (!stack_empty(stk)) {
        node *nd = stack_pop(stk);
        printf("%d ", nd->value);

        node *r = nd->right;
        while (r != NULL) {
            stack_push(stk, r);
            r = r->left;
        }
    }
    stack_free(stk);
    printf("\n");
}
