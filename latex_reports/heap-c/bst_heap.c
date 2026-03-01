#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct bst_node {
    int value;
    struct bst_node *left;
    struct bst_node *right;
} bst_node;

typedef struct bst_tree {
    bst_node *root;
} bst_tree;

static bst_node *construct_bst_node(int val) {
    bst_node *nd = (bst_node*) malloc(sizeof(bst_node));
    if (nd == NULL) return NULL;
    nd->value = val;
    nd->left = NULL;
    nd->right = NULL;
    return nd;
}

static void free_bst_node(bst_node *nd) {
    if (nd != NULL) {
        free_bst_node(nd->left);
        free_bst_node(nd->right);
        free(nd);
    }
}

bst_tree *construct_bst_tree(void) {
    bst_tree *tr = (bst_tree*) malloc(sizeof(bst_tree));
    if (tr == NULL) return NULL;
    tr->root = NULL;
    return tr;
}

void free_bst_tree(bst_tree *tr) {
    if (tr != NULL){
        free_bst_node(tr->root);
        free(tr);
    }
}

/**
 * Recursive helper function to add a value to the BST.
 * @param nd Current node in the recursion
 * @param value Value to insert
 * @return Pointer to the (possibly new) root of this subtree
 */
static bst_node* add_node(bst_node *nd, int value){
    if (nd == NULL){
        return construct_bst_node(value);
    }
    if (value < nd->value){
        nd->left = add_node(nd->left, value);   // Insert in left subtree
    }
    else if (value > nd->value){
        nd->right = add_node(nd->right, value); // Insert in right subtree
    }
    return nd;
}

/**
 * Adds a value to the tree using recursive approach.
 * @param tr Pointer to the tree
 * @param value Value to insert
 */
bool bst_heap_enqueue(bst_tree *tr, int value){
    if (tr == NULL) return false;
    tr->root = add_node(tr->root, value);
    return true;
}

bool bst_heap_dequeue(bst_tree *tr, int* res_ptr) {
    if (tr == NULL || tr->root == NULL) {
        return false;
    }
    bst_node *parent = NULL;
    bst_node *current = tr->root;

    // Traverse to leftmost node
    while (current->left != NULL) {
        parent = current;
        current = current->left;
    }

    *res_ptr = current->value;

    // Case 1: The root is the minimum (no left child at all)
    if (parent == NULL) {
        // Root becomes its right child
        tr->root = current->right;
    }
    else {
        // Parent's left now becomes current's right subtree
        parent->left = current->right;
    }

    free(current);
    return true;
}

/**
 * Recursive helper function to print tree in-order (left, root, right).
 * @param nd Current node in the recursion
 */
static void print(bst_node *nd) {
    if (nd != NULL) {
        print(nd->left);           // Print left subtree
        printf("%d ", nd->value); // Print current node
        print(nd->right);          // Print right subtree
    }
}

/**
 * Prints all values in the tree in sorted order (in-order traversal).
 * @param tr Pointer to the tree
 */
void bst_heap_print(bst_tree *tr) {
    if (tr == NULL) return;
    if (tr->root != NULL)
        print(tr->root);
    printf("\n");
}