#include <stdbool.h>

typedef struct naive_heap1{
    int *arr;
    unsigned int top;
    unsigned int cap;
} naive_heap1;

naive_heap1 *naive_heap1_create(unsigned int cap);
void naive_heap1_free(naive_heap1 *nh);
bool naive_heap1_enqueue(naive_heap1 *nh, int val);
bool naive_heap1_dequeue(naive_heap1 *nh, int *res_ptr);