#include <stdbool.h>
typedef int boolean;

struct binary_tree_node;
struct binary_tree_node *binary_tree_node_create(int value);
void binary_tree_node_destroy(struct binary_tree_node *node);

struct binary_search_tree;
struct binary_search_tree *binary_search_tree_create();
void binary_search_tree_destroy(struct binary_search_tree *tree);
void binary_search_tree_add(struct binary_search_tree *tr, int value);
void binary_search_tree_delete(struct binary_search_tree *tr , int value);
boolean binary_search_tree_find(struct binary_search_tree *tr, int value);
void binary_search_tree_print(struct binary_tree_node *nd);