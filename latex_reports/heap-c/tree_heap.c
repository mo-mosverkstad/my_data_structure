#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Tree-based heap implementation using implicit binary tree structure
// Maintains min-heap property: parent <= children
// Uses size field to keep tree balanced

typedef struct node {
    int value;
    int size;              // number of nodes in subtree (for balancing)
    struct node *left;
    struct node *right;
} node;

typedef struct {
    node *root;
} heap;

node *create_node(int value) {
    node *n = (node *) malloc(sizeof(node));
    if (!n) {
        return NULL;
    }
    n->value = value;
    n->size = 1;      // New node has size 1
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Post-order traversal to free all nodes
void free_node(node *nd){
    if (nd) {
        free_node(nd->left);   // Free left subtree
        free_node(nd->right);  // Free right subtree
        free(nd);              // Free current node
    }
}

heap *create_heap(){
    heap *hp = (heap *) malloc(sizeof(heap));
    if (!hp) return NULL;
    hp->root = NULL;
    return hp;
}

void free_heap(heap* hp){
    if (hp) {
        free_node(hp->root);
        free(hp);
    }
}

// Utility functions

static inline int get_size(node *n) {
    return n ? n->size : 0;
}

static inline void swap_node_values(node *a, node *b) {
    int tmp = a->value;
    a->value = b->value;
    b->value = tmp;
}


/* ---------- INSERT ---------- */
// Recursive insertion maintaining heap property and balance
node *insert_node(node *nd, int value, bool* status_ptr) {
    if (nd == NULL) {
        node *new_node = create_node(value);
        if (!new_node) *status_ptr = false;
        return new_node;
    }

    // Maintain min-heap property: if new value smaller, swap with current
    // Push larger value down the tree
    if (value < nd->value) {
        int tmp = nd->value;
        nd->value = value;
        value = tmp;  // Continue inserting the larger value
    }

    // Insert into subtree with fewer nodes to keep tree balanced
    // This ensures O(log n) height
    if (get_size(nd->left) <= get_size(nd->right))
        nd->left = insert_node(nd->left, value, status_ptr);
    else
        nd->right = insert_node(nd->right, value, status_ptr);

    // Update size after insertion
    nd->size = 1 + get_size(nd->left) + get_size(nd->right);
    return nd;
}

bool tree_heap_enqueue(heap *hp, int value) {
    bool result = true;
    hp->root = insert_node(hp->root, value, &result);
    return result;
}


// Remove minimum (root) and restore heap property
// Recursively promotes smallest child upward
node *remove_node(node *root) {
    if (!root) return NULL;

    // Leaf node: simply remove it
    if (!root->left && !root->right) {
        free(root);
        return NULL;
    }

    // Promote smallest child to maintain heap property
    // This bubbles up the minimum from children
    if (root->left && root->right) {
        // Both children exist: choose smaller one
        if (root->left->value < root->right->value) {
            swap_node_values(root, root->left);
            root->left = remove_node(root->left);  // Recursively remove from left
        } else {
            swap_node_values(root, root->right);
            root->right = remove_node(root->right);  // Recursively remove from right
        }
    }
    else if (root->left) {
        // Only left child exists
        swap_node_values(root, root->left);
        root->left = remove_node(root->left);
    }
    else if (root->right) {
        // Only right child exists
        swap_node_values(root, root->right);
        root->right = remove_node(root->right);
    }

    // Update size after removal
    root->size = 1 + get_size(root->left) + get_size(root->right);
    return root;
}

bool tree_heap_dequeue(heap *hp, int *res_ptr) {
    if (!hp->root) {
        return false;
    }
    *res_ptr = hp->root->value;
    hp->root = remove_node(hp->root);
    return true;
}

// Peek: Return minimum value without removing it - O(1)
// Simply returns root value since min-heap property guarantees root is minimum
bool tree_heap_peek(heap *hp, int *res_ptr) {
    if (!hp->root) {
        return false;  // Empty heap
    }
    *res_ptr = hp->root->value;  // Root always contains minimum
    return true;
}

// Push operation: increment root value and restore heap property
// Returns depth of bubble-down operation for benchmarking
int push(heap *hp, int incr) {
    if (!hp->root)
        return 0;

    hp->root->value += incr;  // Increment root (may violate heap property)
    node *current = hp->root;
    int depth = 0;
    
    // Bubble down: iteratively swap with smaller child
    // Continue until heap property restored
    while (1) {
        node *smallest = current;
        // Find smallest among current node and its children
        if (current->left && current->left->value < smallest->value)
            smallest = current->left;
        if (current->right && current->right->value < smallest->value)
            smallest = current->right;
        
        if (smallest == current)
            break;  // Heap property satisfied
        
        swap_node_values(current, smallest);
        current = smallest;  // Move down to child
        depth++;             // Track depth for analysis
    }
    return depth;
}

// Insert with depth tracking for benchmarking
// Same as insert_node but counts recursion depth
node *insert_node_depth(node *nd, int value, bool* status_ptr, int *depth) {
    if (nd == NULL) {
        node *new_node = create_node(value);
        if (!new_node) *status_ptr = false;
        return new_node;
    }

    // Maintain heap property
    if (value < nd->value) {
        int tmp = nd->value;
        nd->value = value;
        value = tmp;
    }

    (*depth)++;  // Increment depth counter for each level
    
    // Insert into smaller subtree
    if (get_size(nd->left) <= get_size(nd->right))
        nd->left = insert_node_depth(nd->left, value, status_ptr, depth);
    else
        nd->right = insert_node_depth(nd->right, value, status_ptr, depth);

    nd->size = 1 + get_size(nd->left) + get_size(nd->right);
    return nd;
}

int tree_heap_enqueue_depth(heap *hp, int value) {
    bool result = true;
    int depth = 0;
    hp->root = insert_node_depth(hp->root, value, &result, &depth);
    return depth;
}