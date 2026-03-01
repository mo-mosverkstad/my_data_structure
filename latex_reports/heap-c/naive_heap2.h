#include <stdbool.h>

typedef struct naive_heap2{
    int *arr;
    unsigned int top;
    unsigned int cap;
} naive_heap2;

naive_heap2 *naive_heap2_create(unsigned int cap);
void naive_heap2_free(naive_heap2 *nh);
bool naive_heap2_enqueue(naive_heap2 *nh, int val);
bool naive_heap2_dequeue(naive_heap2 *nh, int *res_ptr);