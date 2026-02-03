#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "arrayutil.h"
#include "selectionsort.h"
#include "insertionsort.h"
#include "mergesort.h"
#include "simplemerge.h"
#include "quicksort.h"
#include "bench.h"

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec- t_start->tv_nsec) + (t_stop->tv_sec- t_start->tv_sec)*1000000000;
}

bool is_sorted(int *arr, unsigned int n) {
    if (arr == NULL || n < 2) return true;
    for (unsigned int i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) return false;
    }
    return true;
}

double benchmark_function(int n, void (*sort_func)(int*, unsigned int)){
    if (n <= 0) {
        fprintf(stderr, "Error: n must be positive\n");
        return -1.0;
    }
    int loops = 1;

    struct timespec start, stop;
    volatile int count = 0;
    long total_time = 0;

    for (int i = 0; i < loops; i++) {

        int *array = malloc(n * sizeof(int));
        if (array == NULL) {
            fprintf(stderr, "Failed to allocate keys array\n");
            return -1.0;
        }
        for (int i = 0; i < n; i++)
            array[i] = rand() % 32768;

        clock_gettime(CLOCK_MONOTONIC, &start);
        sort_func(array, n);
        clock_gettime(CLOCK_MONOTONIC, &stop);
        if (is_sorted(array, n)) count++;
        free(array);
        total_time += nano_seconds(&start, &stop);
    }

    if (count != loops) {
        fprintf(stderr, "Error: Sorting failed! %d/%d arrays sorted correctly\n", count, loops);
        return -1.0;
    }

    return (double) total_time/loops;
}

int main(){
    srand(time(NULL));
    /*
    int arr1[] = {124, 817, 273, 848, 298, 737, 372, 653, 201, 2736, 273, 3283, 212, 1, 23, 9773, 9, 5, 1, 1245, 2312, 32, 123, 252};

    printf("SELECTION SORT TEST:\n");
    selection_sort(arr1, sizeof(arr1)/sizeof(int));
    print_array(arr1, sizeof(arr1)/sizeof(int));
    printf("\n\n");

    int arr2[] = {124, 123, 32, 1, 5, 9, 23, 1, 201, 212, 273, 3283, 2736, 653, 372, 9773, 737, 298, 848, 1245, 2312, 273, 817, 252};
    printf("INSERTION SORT TEST:\n");
    insertion_sort(arr2, sizeof(arr2)/sizeof(int));
    print_array(arr2, sizeof(arr2)/sizeof(int));
    printf("\n\n");

    int arr3[] = {124, 817, 273, 848, 298, 737, 372, 653, 201, 2736, 273, 3283, 212, 1, 23, 9773, 9, 5, 1, 1245, 2312, 32, 123, 252};
    printf("MERGE SORT TEST:\n");
    mergesort(arr3, sizeof(arr3)/sizeof(int));
    print_array(arr3, sizeof(arr3)/sizeof(int));
    printf("\n\n");

    
    
    */

    run_benchmark(benchmark_function, quicksort);


    return 0;
}