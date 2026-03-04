#include <stdbool.h>

struct priority_queue {
    void **array;
    unsigned int cap;
    unsigned int size;
    int (*cmp)(const void *, const void *);
};

struct priority_queue* pq_create(unsigned int cap, int (*cmp)(const void *, const void *));
void pq_free(struct priority_queue *pq);
bool pq_enqueue(struct priority_queue *pq, void *value);
bool pq_dequeue(struct priority_queue *pq, void **res_ptr);