#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>


int *unsorted_array_new(int n){
    if (n <= 0) return NULL;
    int *array = (int*) malloc(n*sizeof(int));
    if (array == NULL) return NULL;
    for (int i = 0; i < n; i++)
        array[i] = rand()%(n*2);
    return array;
}

int *sorted_array_new(int n) {
    if (n <= 0) return NULL;
    int *array = (int*)malloc(n*sizeof(int));
    if (array == NULL) return NULL;
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

bool unsorted_search(int array[], int length, int key) {
    for (int index = 0; index < length; index++) {
        if (array[index] == key) {
            return true;
        }
    }
    return false;
}

bool sorted_search(int array[], int length, int key) {
    for (int index = 0; index < length; index++) {
        int value = array[index];
        if (value >= key) {
            return value == key;
        }
    }
    return false;
}


bool binary_search(int array[], unsigned int length, int key) {
    if (length == 0) return false;
    int first = 0;
    int last = length-1;
    while (true) {
        // jump to the middle
        int index = first + (last - first)/2;
        if (array[index] == key) {
            return true;
        }
        if (array[index] < key && index < last) {
            first = index + 1;
            continue;
        }
        if (array[index] > key && index > first) {
            last = index - 1;
            continue;
        }
        return false;
    }
}

bool recursive_binary_search(
    int array[],
    int key,
    unsigned int first,
    unsigned int last
) {
    if (first > last)
        return false;

    unsigned int index = first + (last - first) / 2;

    if (array[index] == key)
        return true;

    if (array[index] < key)
        return recursive_binary_search(array, key, index + 1, last);

    return recursive_binary_search(array, key, first, index - 1);
}

bool wrapped_recursive_binary_search(int array[], unsigned int length, int key){
    if (length == 0) return false;
    return recursive_binary_search(array, key, 0, length-1);
}

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec- t_start->tv_nsec) + (t_stop->tv_sec- t_start->tv_sec)*1000000000;
}

double benchmark_search(int n, int *(*create)(int), bool search(int[], unsigned int, int)) {
    if (n <= 0) {
        fprintf(stderr, "Error: n must be positive\n");
        return -1.0;
    }

    int loops = 1024;

    int *array = create(n);
    if (array == NULL) {
        fprintf(stderr, "Failed to allocate array\n");
        return -1.0;
    }

    int *keys = malloc(loops * sizeof(int));
    if (keys == NULL) {
        fprintf(stderr, "Failed to allocate keys array\n");
        array_destroy(array);
        return -1.0;
    }

    for (int i = 0; i < loops; i++)
        keys[i] = array[rand() % n];

    struct timespec start, stop;
    int hits = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < loops; i++) {
        bool result = search(array, n, keys[i]);
        if (result) {
            hits++;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &stop);

    if (hits < 0) {
        printf("Impossible\n");
    }

    free(keys);
    array_destroy(array);

    return (double) nano_seconds(&start, &stop)/loops;
}

double benchmark_linear_search(int n){
    return benchmark_search(n, unsorted_array_new, unsorted_search);
}

double benchmark_sorted_linear_search(int n){
    return benchmark_search(n, sorted_array_new, sorted_search);
}

double benchmark_binary_search(int n){
    return benchmark_search(n, sorted_array_new, binary_search);
}

double benchmark_recursive_binary_search(int n){
    return benchmark_search(n, sorted_array_new, wrapped_recursive_binary_search);
}


void run_benchmark(double benchmark_function(int)) {
    int SIZE_LENGTH = 7;
    int sizes[] = {256, 2048, 16384, 131072, 1048576, 8388608, 67108864};
    int trials = 16;
    for (int i = 0; i < SIZE_LENGTH; i++) {
        int size = sizes[i];
        double min = DBL_MAX;
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
            printf("ELAPSED TIME PER LOOP: %.2g ns\n", elapsed_time);
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

int main() {
    srand(time(NULL));
    // run_benchmark(benchmark_binary_search);
    run_benchmark(benchmark_recursive_binary_search);
    
    /*
    int array[] = {1, 2, 5, 12, 17, 18, 21};

    printf("Index of 17: %u\n", recursive_binary_search(array, 7, 17, 0, 6));
    printf("Index of 15: %u\n", recursive_binary_search(array, 7, 15, 0, 6));
    */

    return 0;
}