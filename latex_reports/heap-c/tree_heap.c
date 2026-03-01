#include <stdio.h>
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

node *create_node(int value) {
    node *n = (node *) malloc(sizeof(node));
    if (!n) {
        return NULL;
    }
    n->value = value;
    n->size = 1;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// post order free node
void free_node(node *nd){
    if (nd) {
        free_node(nd->left);
        free_node(nd->right);
        free(nd);
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

node *insert_node(node *nd, int value, bool* status_ptr) {
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

    // Insert into subtree with fewer nodes
    if (get_size(nd->left) <= get_size(nd->right))
        nd->left = insert_node(nd->left, value, status_ptr);
    else
        nd->right = insert_node(nd->right, value, status_ptr);

    nd->size = 1 + get_size(nd->left) + get_size(nd->right);
    return nd;
}

bool tree_heap_enqueue(heap *hp, int value) {
    bool result = true;
    hp->root = insert_node(hp->root, value, &result);
    return result;
}


// remove minimum
node *remove_node(node *root) {
    if (!root) return NULL;

    if (!root->left && !root->right) {
        free(root);
        return NULL;
    }

    // Promote smallest child
    if (root->left && root->right) {
        if (root->left->value < root->right->value) {
            swap_node_values(root, root->left);
            root->left = remove_node(root->left);
        } else {
            swap_node_values(root, root->right);
            root->right = remove_node(root->right);
        }
    }
    else if (root->left) {
        swap_node_values(root, root->left);
        root->left = remove_node(root->left);
    }
    else if (root->right) {
        swap_node_values(root, root->right);
        root->right = remove_node(root->right);
    }

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

// push -> increment root
int push(heap *hp, int incr) {
    if (!hp->root)
        return 0;

    hp->root->value += incr;
    node *current = hp->root;
    int depth = 0;
    while (1) {
        node *smallest = current;
        if (current->left && current->left->value < smallest->value)
            smallest = current->left;
        if (current->right && current->right->value < smallest->value)
            smallest = current->right;
        if (smallest == current)
            break;
        swap_node_values(current, smallest);
        current = smallest;
        depth++;
    }
    return depth;
}