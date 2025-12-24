#include <stdio.h>
#include "linked_list.h"
#include "../test_framework/test_framework.h"

int test_create_destroy() {
    struct linked_list *list = linked_list_create();
    ASSERT_TRUE(list != NULL);
    linked_list_destroy(list);
    return 1;
}

int test_add() {
    struct linked_list *list = linked_list_create();
    linked_list_add(list, 1);
    linked_list_add(list, 2);
    linked_list_add(list, 3);
    
    ASSERT_TRUE(linked_list_search(list, 1));
    ASSERT_TRUE(linked_list_search(list, 2));
    ASSERT_TRUE(linked_list_search(list, 3));
    
    linked_list_destroy(list);
    return 1;
}

int test_add_first() {
    struct linked_list *list = linked_list_create();
    linked_list_add_first(list, 1);
    linked_list_add_first(list, 2);
    linked_list_add_first(list, 3);
    
    ASSERT_TRUE(linked_list_search(list, 1));
    ASSERT_TRUE(linked_list_search(list, 2));
    ASSERT_TRUE(linked_list_search(list, 3));
    
    linked_list_destroy(list);
    return 1;
}

int test_search() {
    struct linked_list *list = linked_list_create();
    linked_list_add(list, 5);
    linked_list_add(list, 10);
    
    ASSERT_TRUE(linked_list_search(list, 5));
    ASSERT_TRUE(linked_list_search(list, 10));
    ASSERT_TRUE(!linked_list_search(list, 15));
    
    linked_list_destroy(list);
    return 1;
}

int test_append() {
    struct linked_list *a = linked_list_create();
    struct linked_list *b = linked_list_create();
    
    linked_list_add(a, 1);
    linked_list_add(a, 2);
    linked_list_add(b, 3);
    linked_list_add(b, 4);
    
    linked_list_append(a, b);
    
    ASSERT_TRUE(linked_list_search(a, 1));
    ASSERT_TRUE(linked_list_search(a, 2));
    ASSERT_TRUE(linked_list_search(a, 3));
    ASSERT_TRUE(linked_list_search(a, 4));
    
    linked_list_destroy(a);
    linked_list_destroy(b);
    return 1;
}

int test_fibonacci_sequence() {
    struct linked_list *list = linked_list_create();
    linked_list_add(list, 1);
    linked_list_add(list, 1);
    linked_list_add(list, 2);
    linked_list_add(list, 3);
    linked_list_add(list, 5);
    linked_list_add(list, 8);
    
    ASSERT_TRUE(linked_list_search(list, 1));
    ASSERT_TRUE(linked_list_search(list, 8));
    ASSERT_TRUE(!linked_list_search(list, 13));
    
    linked_list_destroy(list);
    return 1;
}

int test_empty_list_search() {
    struct linked_list *list = linked_list_create();
    ASSERT_TRUE(!linked_list_search(list, 1));
    linked_list_destroy(list);
    return 1;
}

int main() {
    RUN_TEST(test_create_destroy);
    RUN_TEST(test_add);
    RUN_TEST(test_add_first);
    RUN_TEST(test_search);
    RUN_TEST(test_append);
    RUN_TEST(test_fibonacci_sequence);
    RUN_TEST(test_empty_list_search);
    
    TEST_MAIN_END();
}