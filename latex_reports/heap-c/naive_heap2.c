#include <stdlib.h>
#include <stdbool.h>

typedef struct naive_heap2{
    int *arr;
    unsigned int top;
    unsigned int cap;
} naive_heap2;

// return a valid pointer adress if success
// return NULL if failed operation -> detected caller
naive_heap2 *naive_heap2_create(unsigned int cap){
    naive_heap2 *nh = (naive_heap2 *) malloc(sizeof(naive_heap2));
    if (!nh) return NULL;
    int *arr = (int *) malloc(cap * sizeof(int));
    if (!arr){
        free(nh);
        return NULL;
    }
    nh->arr = arr;
    nh->top = 0;
    nh->cap = cap;
    return nh;
}

void naive_heap2_free(naive_heap2 *nh){
    if (!nh) return;
    if (nh->arr){
        free(nh->arr);
    }
    free(nh);
}

// true if success, false if fail
bool naive_heap2_enqueue(naive_heap2 *nh, int val){    
    if (!nh || nh->top >= nh->cap) return false;
    int i = (int) nh->top-1;
    while (i >= 0 && nh->arr[i] < val){
        nh->arr[i+1] = nh->arr[i];
        i--;
    }
    nh->arr[i+1] = val;
    nh->top++;
    return true;
}

// true if success, false if fail. Returned value into res_ptr
bool naive_heap2_dequeue(naive_heap2 *nh, int *res_ptr){
    if (!nh || nh->top == 0 || !res_ptr) return false;
    *res_ptr = nh->arr[--nh->top];
    return true;
}