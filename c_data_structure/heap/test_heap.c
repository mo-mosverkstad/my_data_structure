#include "../test_framework/test_framework.h"
#include "heap.h"

int test_heap_create() {
    struct heap *h = heap_create(10);
    ASSERT_TRUE(h != NULL);
    ASSERT_EQ(0, h->size);
    ASSERT_EQ(10, h->capacity);
    heap_destroy(h);
    return 1;
}

int test_heap_add() {
    struct heap *h = heap_create(5);
    heap_add(h, 4);
    ASSERT_EQ(1, h->size);
    ASSERT_EQ(4, h->arr[0]);
    heap_destroy(h);
    return 1;
}

int test_heap_delete() {
    struct heap *h = heap_create(5);
    heap_add(h, 2);
    heap_add(h, 4);
    heap_add(h, 6);
    int min = heap_delete(h);
    ASSERT_EQ(2, min);
    ASSERT_EQ(2, h->size);
    heap_destroy(h);
    return 1;
}

int main() {
    RUN_TEST(test_heap_create);
    RUN_TEST(test_heap_add);
    RUN_TEST(test_heap_delete);
    TEST_MAIN_END();
}