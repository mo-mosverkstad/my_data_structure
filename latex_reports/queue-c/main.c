#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <float.h>

#include "rawqueue.h"
#include "queue.h"
#include "arrayqueue.h"
#include "bench.h"

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec- t_start->tv_nsec) + (t_stop->tv_sec- t_start->tv_sec)*1000000000;
}

double bench_enqueue(int size) {
    struct timespec start, stop;
    rawqueue *q = rawqueue_create();
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < size; i++) {
        rawqueue_enqueue(q, i);
    }
    clock_gettime(CLOCK_MONOTONIC, &stop);
    long ns = nano_seconds(&start, &stop);
    rawqueue_free(q);
    return (double)ns / size;   // ns per operation
}

double bench_dequeue(int size) {
    struct timespec start, stop;
    rawqueue *q = rawqueue_create();
    for (int i = 0; i < size; i++) {
        rawqueue_enqueue(q, i);
    }
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < size; i++) {
        rawqueue_dequeue(q);
    }
    clock_gettime(CLOCK_MONOTONIC, &stop);
    long ns = nano_seconds(&start, &stop);
    rawqueue_free(q);
    return (double)ns / size;
}



int main(){
    run_benchmark(bench_dequeue);
}