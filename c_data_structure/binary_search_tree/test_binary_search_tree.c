#include <stdio.h>
#include "binary_search_tree.h"
#include "../test_framework/test_framework.h"

int test_create_destroy() {
    struct binary_search_tree *tr = binary_search_tree_create();
    ASSERT_TRUE(tr != NULL);
    binary_search_tree_destroy(tr);
    return 1;
}

int test_add_and_find() {
    struct binary_search_tree *tr = binary_search_tree_create();
    binary_search_tree_add(tr, 12);
    binary_search_tree_add(tr, 6);
    binary_search_tree_add(tr, 15);
    
    ASSERT_EQ(1, binary_search_tree_find(tr, 12));
    ASSERT_EQ(1, binary_search_tree_find(tr, 6));
    ASSERT_EQ(1, binary_search_tree_find(tr, 15));
    ASSERT_EQ(0, binary_search_tree_find(tr, 3));
    
    binary_search_tree_destroy(tr);
    return 1;
}

int test_complex_tree() {
    struct binary_search_tree *tr = binary_search_tree_create();
    binary_search_tree_add(tr, 12);
    binary_search_tree_add(tr, 6);
    binary_search_tree_add(tr, 15);
    binary_search_tree_add(tr, 2);
    binary_search_tree_add(tr, 7);
    binary_search_tree_add(tr, 13);
    binary_search_tree_add(tr, 18);
    binary_search_tree_add(tr, 14);
    
    ASSERT_EQ(1, binary_search_tree_find(tr, 15));
    ASSERT_EQ(0, binary_search_tree_find(tr, 3));
    
    binary_search_tree_destroy(tr);
    return 1;
}

int test_delete() {
    struct binary_search_tree *tr = binary_search_tree_create();
    binary_search_tree_add(tr, 12);
    binary_search_tree_add(tr, 6);
    binary_search_tree_add(tr, 15);
    binary_search_tree_add(tr, 18);
    
    binary_search_tree_delete(tr, 18);
    ASSERT_EQ(0, binary_search_tree_find(tr, 18));
    ASSERT_EQ(1, binary_search_tree_find(tr, 15));
    
    binary_search_tree_destroy(tr);
    return 1;
}

int test_empty_tree() {
    struct binary_search_tree *tr = binary_search_tree_create();
    ASSERT_EQ(0, binary_search_tree_find(tr, 5));
    binary_search_tree_destroy(tr);
    return 1;
}

int test_duplicate_values() {
    struct binary_search_tree *tr = binary_search_tree_create();
    binary_search_tree_add(tr, 10);
    binary_search_tree_add(tr, 10);
    ASSERT_EQ(1, binary_search_tree_find(tr, 10));
    binary_search_tree_destroy(tr);
    return 1;
}

int main() {
    RUN_TEST(test_create_destroy);
    RUN_TEST(test_add_and_find);
    RUN_TEST(test_complex_tree);
    RUN_TEST(test_delete);
    RUN_TEST(test_empty_tree);
    RUN_TEST(test_duplicate_values);
    
    TEST_MAIN_END();
}