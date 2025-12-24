#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int boolean;

struct binary_tree_node {
    int value;
    struct binary_tree_node *left;
    struct binary_tree_node *right;
};

struct binary_tree_node *binary_tree_node_create(int value){
    struct binary_tree_node *new_node = (struct binary_tree_node *) malloc(sizeof(struct binary_tree_node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void binary_tree_node_destroy(struct binary_tree_node *node) {
    if (node == NULL) return;
    binary_tree_node_destroy(node->left);
    binary_tree_node_destroy(node->right);
    free(node);
    node = NULL;
}

struct binary_search_tree {
    struct binary_tree_node *root;
};

struct binary_search_tree *binary_search_tree_create() {
    struct binary_search_tree *tr = (struct binary_search_tree *) malloc(sizeof(struct binary_search_tree));
    tr->root = NULL;
    return tr;
}

void binary_search_tree_destroy(struct binary_search_tree *tree) {
    if (tree == NULL) return;
    binary_tree_node_destroy(tree->root);
    free(tree);
    tree = NULL;
}

struct binary_tree_node *node_add(struct binary_tree_node* nd, int value) {
    if (nd == NULL)
        return binary_tree_node_create(value);
    if (nd->value == value)
        return nd;
    if (nd->value > value)
        nd->left = node_add(nd->left, value);
    else
        nd->right = node_add(nd->right, value);
    return nd;
}


void binary_search_tree_add(struct binary_search_tree *tr, int value) {
    tr->root = node_add(tr->root, value);
}

struct binary_tree_node* promote(struct binary_tree_node *nd) {
    if (nd->left == NULL)
        return nd;
    struct binary_tree_node *nxt = nd;
    while (nxt->left->left != NULL)
        nxt = nxt->left;
    struct binary_tree_node *leftmost = nxt->left;
    nxt->left = leftmost->right;
    leftmost->right = nd;
    return leftmost;
}

struct binary_tree_node* node_delete(struct binary_tree_node* nd, int k) {
    if (nd == NULL) return nd;
    if (nd->value == k) {
        if (nd->left == NULL) {
            struct binary_tree_node *ret = nd->right;
            free(nd);
            return ret;
        }
        if (nd->right == NULL) {
            struct binary_tree_node *ret = nd->left;
            free(nd);
            return ret;
        }
        struct binary_tree_node *leftmost = promote(nd->right);
        leftmost->left = nd->left;
        free(nd);
        return leftmost;
    }
    if (nd->value < k && nd->right != NULL) {
        nd->right = node_delete(nd->right, k);
        return nd;
    }
    if (nd->value > k && nd->left != NULL) {
        nd->left = node_delete(nd->left, k);
        return nd;
    }
    return nd;
}


void binary_search_tree_delete(struct binary_search_tree *tr , int value) {
    if (tr->root == NULL) return;
    tr->root = node_delete(tr->root, value);
}

boolean binary_search_tree_find(struct binary_search_tree *tr, int value) {
    struct binary_tree_node *nd = tr->root;
    while (nd != NULL) {
        if (nd->value == value)
            return true;
        if (nd->value < value)
            nd = nd->right;
        else
            nd = nd->left;
    }
    return false;
}

void binary_search_tree_print(struct binary_tree_node *nd) {
    if (nd == NULL) {
        printf("NULL");
        return;
    }
    printf("(");
    binary_search_tree_print(nd->left);
    printf(", %d, ", nd->value);
    binary_search_tree_print(nd->right);
    printf(")");
}