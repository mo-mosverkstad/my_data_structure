#include <stdlib.h>
#include <stdbool.h>

typedef struct naive_heap1{
    int *arr;
    unsigned int top;
    unsigned int cap;
} naive_heap1;

// return a valid pointer adress if success
// return NULL if failed operation -> detected caller
naive_heap1 *naive_heap1_create(unsigned int cap){
    naive_heap1 *nh = (naive_heap1 *) malloc(sizeof(naive_heap1));
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

void naive_heap1_free(naive_heap1 *nh){
    if (!nh) return;
    if (nh->arr){
        free(nh->arr);
    }
    free(nh);
}

// true if success, false if fail
bool naive_heap1_enqueue(naive_heap1 *nh, int val){
    if (!nh || nh->top >= nh->cap) return false;
    nh->arr[nh->top++] = val;
    return true;
}

// true if success, false if fail. Returned value into res_ptr
bool naive_heap1_dequeue(naive_heap1 *nh, int *res_ptr){
    if (!nh || nh->top == 0 || !res_ptr) return false;
    
    unsigned int min_index = 0;
    int min = nh->arr[0];
    for (unsigned int i = 1; i < nh->top; i++){
        if (nh->arr[i] < min){
            min = nh->arr[i];
            min_index = i;
        }
    }
    
    *res_ptr = min;
    for (unsigned int i = min_index; i < nh->top - 1; i++){
        nh->arr[i] = nh->arr[i + 1];
    }
    nh->top--;
    return true;
}