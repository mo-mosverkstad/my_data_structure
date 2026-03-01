#include <stdlib.h>
#include "tree.h"

/*
typedef struct node {
    int value;
    struct node *right;
    struct node *left;
} node;

typedef struct tree {
    node *root;
} tree;
*/

/**
 * Allocates and initializes a new tree node with the given value.
 * @param val The integer value to store in the node
 * @return Pointer to the newly created node, or NULL if allocation fails
 */
node *construct_node(int val) {
    // Allocate memory for the node structure
    node *nd = (node*) malloc(sizeof(node));
    if (nd == NULL) return NULL; // malloc failed, return NULL
    
    // Initialize node fields
    nd->value = val;   // Store the value
    nd->left = NULL;   // No left child initially
    nd->right = NULL;  // No right child initially
    return nd;
}

/**
 * Recursively frees a node and all its descendants (post-order traversal).
 * @param nd Pointer to the node to free (can be NULL)
 */
void free_node(node *nd) {
    if (nd != NULL) {
        free_node(nd->left);  // Free left subtree
        free_node(nd->right); // Free right subtree
        free(nd);             // Free current node
    }
}

/**
 * Allocates and initializes an empty binary search tree.
 * @return Pointer to the newly created tree, or NULL if allocation fails
 */
tree *construct_tree(void) {
    tree *tr = (tree*) malloc(sizeof(tree));
    if (tr == NULL) return NULL; // Allocation failed
    tr->root = NULL;
    return tr;
}

/**
 * Frees the entire tree including all nodes.
 * @param tr Pointer to the tree to free (can be NULL)
 */
void free_tree(tree *tr) {
    if (tr != NULL){
        free_node(tr->root); // Free all nodes
        free(tr);            // Free tree structure
    }
}