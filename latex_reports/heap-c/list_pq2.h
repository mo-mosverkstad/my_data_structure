#include <stdbool.h>

typedef struct list_pq2{
    int *arr;
    unsigned int top;
    unsigned int cap;
} list_pq2;

list_pq2 *list_pq2_create(unsigned int cap);
void list_pq2_free(list_pq2 *nh);
bool list_pq2_enqueue(list_pq2 *nh, int val);
bool list_pq2_dequeue(list_pq2 *nh, int *res_ptr);
