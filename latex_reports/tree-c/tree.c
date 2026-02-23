#include "tree.h"
#include "stack.h"
#include "arrayqueue.h"
#include <stdio.h>
#include <stdlib.h>

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
void recursive_add(tree *tr, int value){
    if (tr == NULL) return;
    tr->root = add_node(tr->root, value);
}

/**
 * Adds a value to the tree using iterative approach.
 * Traverses the tree to find the correct insertion position.
 * @param tr Pointer to the tree
 * @param value Value to insert
 */
void add(tree *tr, int value){
    if (tr == NULL) return; // Invalid tree
    
    // Track whether we go left or right from parent
    bool left = true;
    node* parent = NULL;  // Parent of current node
    node* nd = tr->root;  // Current node being examined
    
    // Traverse tree to find insertion position
    while (nd != NULL){
        if (value < nd->value){
            parent = nd;      // Remember parent
            nd = nd->left;    // Go left
            left = true;      // Remember we went left
        }
        else if (value > nd->value){
            parent = nd;      // Remember parent
            nd = nd->right;   // Go right
            left = false;     // Remember we went right
        }
        else{
            return; // Duplicate value found, don't insert
        }
    }
    // Loop exits when nd == NULL (found insertion point)
    
    // Create the new node
    node* new_node = construct_node(value);
    
    // Attach new node to tree
    if (parent == NULL){
        tr->root = new_node; // Tree was empty, new node becomes root
    }
    else{
        // Attach to parent's left or right based on where we went
        if (left){
            parent->left = new_node;
        }
        else{
            parent->right = new_node;
        }        
    }
}

/**
 * Recursive helper function to search for a value in the BST.
 * @param nd Current node in the recursion
 * @param value Value to search for
 * @return true if value is found, false otherwise
 */
static bool lookup_node(node *nd, int value){
    if (nd == NULL) return false; // Not found
    if (value < nd->value) return lookup_node(nd->left, value);
    else if (value > nd->value) return lookup_node(nd->right, value);
    return true; // Found
}

/**
 * Searches for a value in the tree using recursive approach.
 * @param tr Pointer to the tree
 * @param value Value to search for
 * @return true if value exists in tree, false otherwise
 */
bool recursive_lookup(tree *tr, int value){
    if (tr == NULL) return false;
    return lookup_node(tr->root, value);
}

/**
 * Searches for a value in the tree using iterative approach.
 * @param tr Pointer to the tree
 * @param value Value to search for
 * @return true if value exists in tree, false otherwise
 */
bool tree_lookup_iterative(const tree *tr, int value) {
    if (tr == NULL) return false;
    const node *nd = tr->root;
    while (nd != NULL) {
        if (value == nd->value) return true; // Found
        nd = (value < nd->value) ? nd->left : nd->right;
    }
    return false; // Not found
}

/**
 * Promotes the leftmost node of a subtree to become the new root.
 * Used during deletion when a node has two children.
 * @param nd Root of the subtree
 * @return Pointer to the promoted (leftmost) node
 */
node *promote(node *nd) {
    // If no left child, this node is already leftmost
    if (nd->left == NULL)
        return nd;
    
    // Find the leftmost node and its parent
    node *nxt = nd;  // Will be parent of leftmost
    // Traverse down left edges until we find leftmost
    while (nxt->left->left != NULL)
        nxt = nxt->left;
    
    // nxt->left is now the leftmost node
    node* leftmost = nxt->left;
    
    // Detach leftmost from its parent
    // Leftmost's right child (if any) takes its place
    nxt->left = nxt->left->right;
    
    // Make leftmost the new root of this subtree
    // Original root (nd) becomes right child of leftmost
    leftmost->right = nd;
    
    return leftmost;
}

/**
 * Recursive helper function to delete a node with value k from the BST.
 * Handles three cases: leaf node, one child, two children.
 * @param nd Current node in the recursion
 * @param k Value to delete
 * @return Pointer to the new root of this subtree
 */
node* node_delete(node *nd, int k){
    if (nd == NULL) return NULL; // Value not found
    if (nd->value == k){
        node *left = nd->left;
        node *right = nd->right;
        // Case 1: Leaf node
        if (left == NULL && right == NULL){
            free_node(nd);
            return NULL;
        }
        // Case 2: Only right child
        if (left == NULL){
            node *ret = nd->right;
            free(nd);
            return ret;
        }
        // Case 3: Only left child
        else if (right == NULL){
            node *ret = nd->left;
            free(nd);
            return ret;
        }
        // Case 4: Both children exist - promote leftmost of right subtree
        else{
            node *promoted = promote(nd->right);
            promoted->left = nd->left;
            free(nd);
            return promoted;
        }
    }
    // Recursively search in appropriate subtree
    if (nd->value < k && nd->right != NULL){
        nd->right = node_delete(nd->right, k);
        return nd;
    }
    if (nd->value > k && nd->left != NULL){
        nd->left = node_delete(nd->left, k);
        return nd;
    }
    return nd; // Value not in this subtree
}

/**
 * Deletes a value from the tree.
 * @param tr Pointer to the tree
 * @param k Value to delete
 */
void tree_delete(tree *tr, int k){
    if (tr == NULL) return;
    tr->root = node_delete(tr->root, k);
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
void print_tree(tree *tr) {
    if (tr == NULL) return;
    if (tr->root != NULL)
        print(tr->root);
    printf("\n");
}

/**
 * Prints tree values in-order using an explicit stack (iterative approach).
 * Simulates the call stack of recursive in-order traversal.
 * @param tr Pointer to the tree
 */
void tree_print_inorder_stack(const tree *tr) {
    if (tr == NULL) return; // Invalid tree
    
    // Create stack for iterative traversal
    stack *stk = stack_create();
    node *nd = tr->root;

    // Phase 1: Push all left nodes to stack (go to leftmost)
    while (nd != NULL) {
        stack_push(stk, nd);  // Save node for later processing
        nd = nd->left;        // Go left
    }

    // Phase 2: Process nodes in order
    while (!stack_empty(stk)) {
        // Pop and print node (this is the "visit" step)
        node *nd = stack_pop(stk);
        printf("%d ", nd->value);

        // Phase 3: Process right subtree
        // Push all left nodes of right subtree
        node *r = nd->right;
        while (r != NULL) {
            stack_push(stk, r);  // Save for later
            r = r->left;         // Go left
        }
    }
    
    // Clean up
    stack_free(stk);
    printf("\n");
}

/**
 * Prints tree values in breadth-first (level-order) traversal.
 * Uses a queue to process nodes level by level.
 * @param tr Pointer to the tree
 */
void breadth_first_print(const tree *tr){
    if (tr == NULL) return; // Invalid tree
    
    // Create queue for BFS traversal
    arrayqueue *queue = arrayqueue_create();
    node *current = tr->root;
    
    // Process nodes level by level
    while (current != NULL){
        // Visit current node
        printf("%d ", current->value);
        
        // Enqueue children for later processing (left to right)
        if (current->left != NULL) 
            arrayqueue_enqueue(queue, current->left);
        if (current->right != NULL) 
            arrayqueue_enqueue(queue, current->right);
        
        // Get next node from queue (NULL if queue empty)
        current = arrayqueue_dequeue(queue);
    }
    
    // Clean up
    arrayqueue_free(queue);
    printf("\n");
}