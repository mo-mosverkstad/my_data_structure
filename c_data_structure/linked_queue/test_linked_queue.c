#include <stdio.h>
#include <string.h>
#include "linked_queue.h"
#include "../test_framework/test_framework.h"

int test_create_destroy() {
    struct linked_queue *queue = linked_queue_create();
    ASSERT_TRUE(queue != NULL);
    linked_queue_destroy(queue);
    return 1;
}

int test_enqueue_dequeue() {
    struct linked_queue *queue = linked_queue_create();
    char *test_str = "test";
    
    linked_queue_enqueue(queue, test_str);
    char *result = (char*)linked_queue_dequeue(queue);
    
    ASSERT_TRUE(result != NULL);
    ASSERT_TRUE(strcmp(result, "test") == 0);
    
    linked_queue_destroy(queue);
    return 1;
}

int test_fifo_order() {
    struct linked_queue *queue = linked_queue_create();
    
    linked_queue_enqueue(queue, "first");
    linked_queue_enqueue(queue, "second");
    linked_queue_enqueue(queue, "third");
    
    char *result1 = (char*)linked_queue_dequeue(queue);
    char *result2 = (char*)linked_queue_dequeue(queue);
    char *result3 = (char*)linked_queue_dequeue(queue);
    
    ASSERT_TRUE(strcmp(result1, "first") == 0);
    ASSERT_TRUE(strcmp(result2, "second") == 0);
    ASSERT_TRUE(strcmp(result3, "third") == 0);
    
    linked_queue_destroy(queue);
    return 1;
}

int test_dequeue_empty() {
    struct linked_queue *queue = linked_queue_create();
    const void *result = linked_queue_dequeue(queue);
    ASSERT_TRUE(result == NULL);
    linked_queue_destroy(queue);
    return 1;
}

int test_example_sequence() {
    struct linked_queue *queue = linked_queue_create();
    
    linked_queue_enqueue(queue, "Hello");
    linked_queue_enqueue(queue, "world");
    linked_queue_enqueue(queue, "!");
    linked_queue_enqueue(queue, "How");
    linked_queue_enqueue(queue, "are");
    
    char *results[8];
    for (int i = 0; i < 8; i++) {
        results[i] = (char*)linked_queue_dequeue(queue);
    }
    
    ASSERT_TRUE(strcmp(results[0], "Hello") == 0);
    ASSERT_TRUE(strcmp(results[1], "world") == 0);
    ASSERT_TRUE(strcmp(results[2], "!") == 0);
    ASSERT_TRUE(strcmp(results[3], "How") == 0);
    ASSERT_TRUE(strcmp(results[4], "are") == 0);
    ASSERT_TRUE(results[5] == NULL);
    ASSERT_TRUE(results[6] == NULL);
    ASSERT_TRUE(results[7] == NULL);
    
    linked_queue_destroy(queue);
    return 1;
}

int test_mixed_operations() {
    struct linked_queue *queue = linked_queue_create();
    
    linked_queue_enqueue(queue, "A");
    char *result1 = (char*)linked_queue_dequeue(queue);
    ASSERT_TRUE(strcmp(result1, "A") == 0);
    
    linked_queue_enqueue(queue, "B");
    linked_queue_enqueue(queue, "C");
    char *result2 = (char*)linked_queue_dequeue(queue);
    char *result3 = (char*)linked_queue_dequeue(queue);
    
    ASSERT_TRUE(strcmp(result2, "B") == 0);
    ASSERT_TRUE(strcmp(result3, "C") == 0);
    
    linked_queue_destroy(queue);
    return 1;
}

int test_integer_pointers() {
    struct linked_queue *queue = linked_queue_create();
    int values[] = {10, 20, 30};
    
    linked_queue_enqueue(queue, &values[0]);
    linked_queue_enqueue(queue, &values[1]);
    linked_queue_enqueue(queue, &values[2]);
    
    int *result1 = (int*)linked_queue_dequeue(queue);
    int *result2 = (int*)linked_queue_dequeue(queue);
    int *result3 = (int*)linked_queue_dequeue(queue);
    
    ASSERT_EQ(10, *result1);
    ASSERT_EQ(20, *result2);
    ASSERT_EQ(30, *result3);
    
    linked_queue_destroy(queue);
    return 1;
}

int main() {
    RUN_TEST(test_create_destroy);
    RUN_TEST(test_enqueue_dequeue);
    RUN_TEST(test_fifo_order);
    RUN_TEST(test_dequeue_empty);
    RUN_TEST(test_example_sequence);
    RUN_TEST(test_mixed_operations);
    RUN_TEST(test_integer_pointers);
    
    TEST_MAIN_END();
}