#include "../test_framework/test_framework.h"
#include "hashtable.h"

int test_hashtable_create() {
    struct hashtable* table = hashtable_create(hash2);
    ASSERT_TRUE(table != NULL);
    hashtable_destroy(table);
    return 1;
}

int test_hashtable_add() {
    struct hashtable* table = hashtable_create(hash2);
    hashtable_insert(table, "apple", 5);
    hashtable_insert(table, "banana", 7);
    hashtable_insert(table, "orange", 3);

    ASSERT_EQ(5, hashtable_search(table, "apple"));
    ASSERT_EQ(7, hashtable_search(table, "banana"));
    ASSERT_EQ(3, hashtable_search(table, "orange"));

    hashtable_destroy(table);
    return 1;
}

int test_hashtable_delete() {
    struct hashtable* table = hashtable_create(hash2);
    hashtable_insert(table, "apple", 5);
    hashtable_insert(table, "banana", 7);
    hashtable_insert(table, "orange", 3);

    hashtable_delete(table, "orange");

    ASSERT_EQ(5, hashtable_search(table, "apple"));
    ASSERT_EQ(7, hashtable_search(table, "banana"));
    ASSERT_EQ(-1, hashtable_search(table, "orange"));
    hashtable_print(table);
    
    hashtable_destroy(table);
    return 1;
}

int main() {
    RUN_TEST(test_hashtable_create);
    RUN_TEST(test_hashtable_add);
    RUN_TEST(test_hashtable_delete);
    TEST_MAIN_END();
}