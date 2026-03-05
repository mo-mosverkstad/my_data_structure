#include <stdbool.h>

typedef struct list_pq1{
    int *arr;
    unsigned int top;
    unsigned int cap;
} list_pq1;

list_pq1 *list_pq1_create(unsigned int cap);
void list_pq1_free(list_pq1 *nh);
bool list_pq1_enqueue(list_pq1 *nh, int val);
bool list_pq1_dequeue(list_pq1 *nh, int *res_ptr);
