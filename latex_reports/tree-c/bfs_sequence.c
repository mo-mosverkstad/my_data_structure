/**
 * Breadth-first sequence iterator for binary trees.
 * Provides an iterator-style interface to traverse a tree level by level.
 */

#include <stdio.h>
#include <stdlib.h>
#include "arrayqueue.h"
#include "tree.h"
#include "bfs_sequence.h"

/**
 * Creates a new breadth-first sequence iterator for the given tree.
 * Initializes the internal queue with the root node.
 * @param tr Pointer to the tree to iterate over
 * @return Pointer to the new sequence, or NULL if allocation fails or tree is empty
 */
sequence *create_sequence(tree *tr){
    // Validate input: tree must exist and have a root
    if (tr == NULL || tr->root == NULL) return NULL;
    
    // Allocate memory for the sequence structure
    sequence *seq = (sequence *) malloc(sizeof(sequence));
    if (seq == NULL) return NULL; // malloc failed
    
    // Create the internal queue for BFS traversal
    seq->queue = arrayqueue_create();
    if (seq->queue == NULL) {
        free(seq); // Queue creation failed, clean up sequence
        return NULL;
    }
    
    // Initialize queue with root node to start traversal
    arrayqueue_enqueue(seq->queue, tr->root);
    return seq;
}

void free_sequence(sequence *seq){
    // Validate sequence pointer
    if (seq == NULL) return;

    // Free the internal queue
    arrayqueue_free(seq->queue);

    // Free the sequence structure itself
    free(seq);
}

/**
 * Returns the next value in the breadth-first traversal.
 * Automatically enqueues the children of the current node.
 * @param seq Pointer to the sequence iterator
 * @return Value of the next node, or 0 if sequence is exhausted or invalid
 */
int next(sequence *seq){
    // Validate sequence pointer
    if (seq == NULL) return 0;
    
    // Check if there are more nodes to process
    if (arrayqueue_empty(seq->queue)){
        return 0; // Traversal complete
    }
    
    // Get the next node from the queue
    node *nd = arrayqueue_dequeue(seq->queue);
    if (nd == NULL){
        return 0; // Dequeue failed (shouldn't happen if queue not empty)
    }
    
    // Enqueue left child if it exists
    if (nd->left != NULL) arrayqueue_enqueue(seq->queue, nd->left);
    // Enqueue right child if it exists
    if (nd->right != NULL) arrayqueue_enqueue(seq->queue, nd->right);
    
    // Return the value of the current node
    return nd->value;
}