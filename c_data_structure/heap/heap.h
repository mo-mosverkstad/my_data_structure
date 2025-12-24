#ifndef HEAP_H
#define HEAP_H

struct heap {
    int *arr;
    int size;
    int capacity;
};

struct heap *heap_create(int capacity);
void heap_destroy(struct heap *h);
void heap_add(struct heap *h, int val);
int heap_delete(struct heap *h);
void heap_print(struct heap *h);

#endif