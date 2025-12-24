#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>

static int test_failures = 0;

#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf("FAIL: %s:%d - Expected %d, got %d\n", __FILE__, __LINE__, (expected), (actual)); \
            return 0; \
        } \
    } while(0)

#define ASSERT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s:%d - Condition failed\n", __FILE__, __LINE__); \
            return 0; \
        } \
    } while(0)

#define RUN_TEST(test_func) \
    do { \
        printf("Running %s... ", #test_func); \
        if (test_func()) { \
            printf("PASS\n"); \
        } else { \
            printf("FAIL\n"); \
            test_failures++; \
        } \
    } while(0)

#define TEST_MAIN_END() \
    do { \
        if (test_failures > 0) { \
            printf("\nTests failed: %d\n", test_failures); \
            exit(1); \
        } \
        printf("\nAll tests passed!\n"); \
        exit(0); \
    } while(0)

#endif