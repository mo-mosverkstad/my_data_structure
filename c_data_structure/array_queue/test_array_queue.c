#include <stdio.h>
#include "array_queue.h"
#include "../test_framework/test_framework.h"

int test_create_destroy() {
    struct array_queue *queue = array_queue_create();
    ASSERT_TRUE(queue != NULL);
    array_queue_destroy(queue);
    return 1;
}

int test_empty_queue() {
    struct array_queue *queue = array_queue_create();
    ASSERT_TRUE(array_queue_is_empty(queue));
    ASSERT_TRUE(!array_queue_is_full(queue));
    array_queue_destroy(queue);
    return 1;
}

int test_enqueue_dequeue() {
    struct array_queue *queue = array_queue_create();
    int value = 42;
    
    array_queue_enqueue(queue, &value);
    ASSERT_TRUE(!array_queue_is_empty(queue));
    
    int *result = (int*)array_queue_dequeue(queue);
    ASSERT_TRUE(result != NULL);
    ASSERT_EQ(42, *result);
    ASSERT_TRUE(array_queue_is_empty(queue));
    
    array_queue_destroy(queue);
    return 1;
}

int test_multiple_items() {
    struct array_queue *queue = array_queue_create();
    int values[] = {1, 2, 3, 4, 5};
    
    for (int i = 0; i < 5; i++) {
        array_queue_enqueue(queue, &values[i]);
    }
    
    for (int i = 0; i < 5; i++) {
        int *result = (int*)array_queue_dequeue(queue);
        ASSERT_TRUE(result != NULL);
        ASSERT_EQ(values[i], *result);
    }
    
    array_queue_destroy(queue);
    return 1;
}

int test_full_queue() {
    struct array_queue *queue = array_queue_create();
    int values[16];
    
    for (int i = 0; i < 16; i++) {
        values[i] = i;
        array_queue_enqueue(queue, &values[i]);
    }
    
    ASSERT_TRUE(array_queue_is_full(queue));
    
    array_queue_destroy(queue);
    return 1;
}

int test_dequeue_empty() {
    struct array_queue *queue = array_queue_create();
    void *result = array_queue_dequeue(queue);
    ASSERT_TRUE(result == NULL);
    array_queue_destroy(queue);
    return 1;
}

int test_circular_behavior() {
    struct array_queue *queue = array_queue_create();
    int values[20];
    
    for (int i = 0; i < 20; i++) {
        values[i] = i;
    }
    
    // Fill queue (15 items max due to SIZE-1 limitation)
    for (int i = 0; i < 15; i++) {
        array_queue_enqueue(queue, &values[i]);
    }
    
    // Dequeue some items
    for (int i = 0; i < 5; i++) {
        int *result = (int*)array_queue_dequeue(queue);
        ASSERT_EQ(i, *result);
    }
    
    // Add more items to test circular behavior
    for (int i = 15; i < 20; i++) {
        array_queue_enqueue(queue, &values[i]);
    }
    
    array_queue_destroy(queue);
    return 1;
}

int main() {
    RUN_TEST(test_create_destroy);
    RUN_TEST(test_empty_queue);
    RUN_TEST(test_enqueue_dequeue);
    RUN_TEST(test_multiple_items);
    RUN_TEST(test_full_queue);
    RUN_TEST(test_dequeue_empty);
    RUN_TEST(test_circular_behavior);
    
    TEST_MAIN_END();
}