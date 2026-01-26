#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

int *unsorted_array_new(int n){
    int *array = (int*) malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
        array[i] = rand()%(n*2);
    return array;
}

int *sorted_array_new(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    int nxt = 0;
    for (int i = 0; i < n ; i++) {
        nxt += rand()%10 + 1;
        array[i] = nxt;
    }
    return array;
}

void array_destroy(int *array){
    if (array != NULL){
        free(array);
    }
}

unsigned int unsorted_search(int array[], unsigned int length, int key) {
    for (int index = 0; index < length; index++) {
        if (array[index] == key) {
            return index;
        }
    }
    return UINT_MAX;
}


unsigned int binary_search(int array[], unsigned int length, int key) {
    int first = 0;
    int last = length-1;
    while (true) {
        // jump to the middle
        int index = (first + last)/2;
        if (array[index] == key) {
            return index;
        }
        if (array[index] < key && index < last) {
            // what is the first possible page?
            first = ...... ;
            continue;
        }
        if (array[index] > key && index > first) {
            // what is the last possible page?
            last = ...... ;
            continue;
    }
    // Why do we land here? What should we do?
    }
}

/*
bool recursive_binary_search(int[] array, int length, int key, int first, int last) {
    // jump to the middle
    int index = ....... ;
    if (array[index] == key) {
    // hmm what now?
    }
    if (array[index] < key && index < last) {
    // call recursive but narrow the search
    }
    if (array[index] > key && index > first) {
    // call recursive but narrow the search
    }
    // as before
}
*/

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec- t_start->tv_nsec) + (t_stop->tv_sec- t_start->tv_sec)*1000000000;
}

double benchmark_search(int n, unsigned int search(int[], unsigned int, int)) {
    srand(time(NULL));
    int loops = 1024;

    int *array = unsorted_array_new(n);
    int *keys  = malloc(loops * sizeof(int));

    for (int i = 0; i < loops; i++)
        keys[i] = array[rand() % n];

    struct timespec start, stop;
    volatile int hits = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < loops; i++) {
        int result = search(array, n, keys[i]);
        if (result != UINT_MAX){
            hits++;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &stop);

    free(keys);
    array_destroy(array);

    return (double) nano_seconds(&start, &stop)/loops;
}

double benchmark_linear_search(int n){
    return benchmark_search(n, unsorted_search);
}


void run_benchmark(double benchmark_function(int)) {
    int SIZE_LENGTH = 8;
    int sizes[] = {1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072};
    int trials = 16;
    for (int i = 0; i < SIZE_LENGTH; i++) {
        int size = sizes[i];
        double min = LONG_MAX;
        double max = 0;
        double total = 0;
        
        printf("--- BENCHMARK MEASUREMENTS (%d, %d SIZE) ---\n", i, size);
        for (int j = 0; j < trials; j++) {
            double elapsed_time = benchmark_function(size);
            if (elapsed_time < min){
                min = elapsed_time;
            }
            if (elapsed_time > max){
                max = elapsed_time;
            }
            total += elapsed_time;
            printf("ELAPSED TIME: TOTAL: %.2g ns, AVG PER LOOP: %.2g ns\n", elapsed_time, elapsed_time);
        }
        printf("\n");
    
        printf("--- BENCHMARK SUMMARY (%d) ---\n", i);
        printf("MAX TIME: %.2g ns/operation \n", max);
        printf("MIN TIME: %.2g ns/operation \n", min);
        printf("AVG TIME: %.2g ns/operation \n", total/trials);
        printf("TOT TIME: %.2g ns/operation \n", total);
        printf("\n\n");
    }
}

int main(){
    run_benchmark(benchmark_linear_search);
    return 0;
}