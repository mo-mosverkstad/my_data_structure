#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct priority_queue {
    void **array;
    unsigned int cap;
    unsigned int size;
    int (*cmp)(const void *, const void *);
};

struct priority_queue* pq_create(unsigned int cap, int (*cmp)(const void *, const void *)) {
    struct priority_queue* pq = malloc(sizeof(struct priority_queue));
    if (!pq) return NULL;

    pq->array = malloc(cap * sizeof(void *));
    if (!pq->array) {
        free(pq);
        return NULL;
    }

    pq->cap = cap;
    pq->size = 0;
    pq->cmp = cmp;
    return pq;
}

void pq_free(struct priority_queue *pq) {
    if (!pq) return;
    free(pq->array);
    free(pq);
}

static inline void swap(void **a, void **b) {
    void *tmp = *a;
    *a = *b;
    *b = tmp;
}

static void bubble_up(struct priority_queue *pq, unsigned int index) {
    while (index > 0) {
        unsigned int parent = (index - 1) / 2;

        if (pq->cmp(pq->array[index], pq->array[parent]) >= 0)
            break;
        swap(&pq->array[index], &pq->array[parent]);
        index = parent;
    }
}

bool pq_enqueue(struct priority_queue *pq, void *value) {
    if (pq->size >= pq->cap) return false;  // full
    pq->array[pq->size] = value;
    bubble_up(pq, pq->size);
    pq->size++;
    return true;
}

static void sink_down(struct priority_queue *pq, unsigned int index) {
    while (1) {
        unsigned int left = 2 * index + 1;
        unsigned int right = 2 * index + 2;
        unsigned int smallest = index;

        if (left < pq->size && pq->cmp(pq->array[left], pq->array[smallest]) < 0)
            smallest = left;
        if (right < pq->size && pq->cmp(pq->array[right], pq->array[smallest]) < 0)
            smallest = right;
        if (smallest == index)
            break;
        swap(&pq->array[index], &pq->array[smallest]);
        index = smallest;
    }
}

bool pq_dequeue(struct priority_queue *pq, void **res_ptr) {
    if (pq->size == 0) return false;  // empty
    *res_ptr = pq->array[0];
    pq->size--;
    pq->array[0] = pq->array[pq->size];
    sink_down(pq, 0);
    return true;
}