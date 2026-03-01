#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Recursive helper function to add a value to the BST.
 * @param nd Current node in the recursion
 * @param value Value to insert
 * @return Pointer to the (possibly new) root of this subtree
 */
static node* add_node(node *nd, int value){
    if (nd == NULL){
        return construct_node(value); // Base case: create new node
    }
    if (value < nd->value){
        nd->left = add_node(nd->left, value);   // Insert in left subtree
    }
    else if (value > nd->value){
        nd->right = add_node(nd->right, value); // Insert in right subtree
    }
    // If value == nd->value, duplicate - don't insert
    return nd;
}

/**
 * Adds a value to the tree using recursive approach.
 * @param tr Pointer to the tree
 * @param value Value to insert
 */
bool tree_heap_enqueue(tree *tr, int value){
    if (tr == NULL) return false;
    tr->root = add_node(tr->root, value);
    return true;
}

bool tree_heap_dequeue(tree *tr, int* res_ptr) {
    if (tr == NULL || tr->root == NULL) {
        return false;
    }
    node *parent = NULL;
    node *current = tr->root;

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
static void print(node *nd) {
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
void tree_heap_print(tree *tr) {
    if (tr == NULL) return;
    if (tr->root != NULL)
        print(tr->root);
    printf("\n");
}