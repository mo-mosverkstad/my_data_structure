#include <stdio.h>
#include "linked_list_raw.h"
#include "../test_framework/test_framework.h"

int test_create_destroy() {
    struct linked_list_raw *list = create_linked_list_raw();
    ASSERT_TRUE(list != NULL);
    linked_list_destroy(list);
    return 1;
}

int test_add_search() {
    struct linked_list_raw *list = create_linked_list_raw();
    linked_list_raw_add(list, 1);
    linked_list_raw_add(list, 2);
    linked_list_raw_add(list, 3);
    
    ASSERT_TRUE(linked_list_search(list, 1));
    ASSERT_TRUE(linked_list_search(list, 2));
    ASSERT_TRUE(linked_list_search(list, 3));
    ASSERT_TRUE(!linked_list_search(list, 4));
    
    linked_list_destroy(list);
    return 1;
}

int test_delete() {
    struct linked_list_raw *list = create_linked_list_raw();
    linked_list_raw_add(list, 1);
    linked_list_raw_add(list, 4);
    linked_list_raw_add(list, 9);
    linked_list_raw_add(list, 16);
    
    linked_list_raw_delete(list, 9);
    ASSERT_TRUE(!linked_list_search(list, 9));
    ASSERT_TRUE(linked_list_search(list, 1));
    ASSERT_TRUE(linked_list_search(list, 4));
    ASSERT_TRUE(linked_list_search(list, 16));
    
    linked_list_destroy(list);
    return 1;
}

int test_append() {
    struct linked_list_raw *a = create_linked_list_raw();
    struct linked_list_raw *b = create_linked_list_raw();
    
    linked_list_raw_add(a, 1);
    linked_list_raw_add(a, 2);
    linked_list_raw_add(b, 3);
    linked_list_raw_add(b, 4);
    
    linked_list_raw_append(a, b);
    
    ASSERT_TRUE(linked_list_search(a, 1));
    ASSERT_TRUE(linked_list_search(a, 2));
    ASSERT_TRUE(linked_list_search(a, 3));
    ASSERT_TRUE(linked_list_search(a, 4));
    
    linked_list_destroy(a);
    linked_list_destroy(b);
    return 1;
}

int test_fibonacci_with_delete() {
    struct linked_list_raw *list = create_linked_list_raw();
    linked_list_raw_add(list, 1);
    linked_list_raw_add(list, 1);
    linked_list_raw_add(list, 2);
    linked_list_raw_add(list, 3);
    linked_list_raw_add(list, 5);
    linked_list_raw_add(list, 8);
    linked_list_raw_add(list, 13);
    
    ASSERT_TRUE(linked_list_search(list, 8));
    linked_list_raw_delete(list, 8);
    ASSERT_TRUE(!linked_list_search(list, 8));
    ASSERT_TRUE(linked_list_search(list, 13));
    
    linked_list_destroy(list);
    return 1;
}

int test_reverse() {
    struct linked_list_raw *list = create_linked_list_raw();
    linked_list_raw_add(list, 1);
    linked_list_raw_add(list, 2);
    linked_list_raw_add(list, 3);
    
    linked_list_reverse(list);
    
    ASSERT_TRUE(linked_list_search(list, 1));
    ASSERT_TRUE(linked_list_search(list, 2));
    ASSERT_TRUE(linked_list_search(list, 3));
    
    linked_list_destroy(list);
    return 1;
}

int test_sort() {
    struct linked_list_raw *list = create_linked_list_raw();
    linked_list_raw_add(list, 3);
    linked_list_raw_add(list, 1);
    linked_list_raw_add(list, 4);
    linked_list_raw_add(list, 2);
    
    linked_list_sort(list);
    
    ASSERT_TRUE(linked_list_search(list, 1));
    ASSERT_TRUE(linked_list_search(list, 2));
    ASSERT_TRUE(linked_list_search(list, 3));
    ASSERT_TRUE(linked_list_search(list, 4));
    
    linked_list_destroy(list);
    return 1;
}

int test_empty_operations() {
    struct linked_list_raw *list = create_linked_list_raw();
    
    ASSERT_TRUE(!linked_list_search(list, 1));
    linked_list_raw_delete(list, 1);
    linked_list_reverse(list);
    linked_list_sort(list);
    
    linked_list_destroy(list);
    return 1;
}

int main() {
    RUN_TEST(test_create_destroy);
    RUN_TEST(test_add_search);
    RUN_TEST(test_delete);
    RUN_TEST(test_append);
    RUN_TEST(test_fibonacci_with_delete);
    RUN_TEST(test_reverse);
    RUN_TEST(test_sort);
    RUN_TEST(test_empty_operations);
    
    TEST_MAIN_END();
}