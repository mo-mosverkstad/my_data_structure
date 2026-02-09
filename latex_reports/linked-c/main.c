#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "linked.h"
#include "bench.h"

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec- t_start->tv_nsec) + (t_stop->tv_sec- t_start->tv_sec)*1000000000;
}


void test(){
    linked *lnk1 = linked_create();
    
    linked_add(lnk1, 18);
    linked_add(lnk1, 35);
    linked_add(lnk1, 97);
    linked_add(lnk1, 17);
    linked_add(lnk1, 22);
    linked_add(lnk1, 58);
    linked_add(lnk1, 1024);
    linked_add(lnk1, 3211);
    linked_add(lnk1, 90);
    
    printf("Linked list 1 (%d): ", linked_length(lnk1));
    linked_print(lnk1);
    
    linked *lnk2 = linked_create();
    
    linked_add(lnk2, 79);
    linked_add(lnk2, 83);
    linked_add(lnk2, 22);
    linked_add(lnk2, 132);
    linked_add(lnk2, 531);
    linked_add(lnk2, 322);
    linked_add(lnk2, 1534);
    
    printf("Linked list 2 (%d): ", linked_length(lnk2));
    linked_print(lnk2);
    
    linked_append(lnk1, lnk2);
    
    printf("Linked list 1 (%d): ", linked_length(lnk1));
    linked_print(lnk1);
    
    printf("Linked list 2 (%d): ", linked_length(lnk2));
    linked_print(lnk2);
    
    linked_free(lnk1);
    linked_free(lnk2);
}

double benchmark_function(int n){
    if (n <= 0) {
        fprintf(stderr, "Error: n must be positive\n");
        return -1.0;
    }
    int loops = 512;

    struct timespec start, stop;
    volatile int count = 0;
    long total_time = 0;
    
    linked **a = malloc(sizeof(linked*) * loops);
    linked **b = malloc(sizeof(linked*) * loops);
    if (a == NULL || b == NULL) {
        fprintf(stderr, "Failed to allocate linked list preallocations\n");
        return -1.0;
    }
    
    for (int i = 0; i < loops; i++){
        a[i] = linked_create();
        if (a[i] == NULL) {
            fprintf(stderr, "Failed to allocate linked list\n");
            return -1.0;
        }
        for (int k = 0; k < 8192; k++)
            linked_add(a[i], k);
        
        b[i] = linked_create();
        if (b[i] == NULL) {
            fprintf(stderr, "Failed to allocate linked list\n");
            return -1.0;
        }
        for (int k = 0; k < n; k++)
            linked_add(b[i], k);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < loops; i++) {
        linked_append(a[i], b[i]);        
        count++;
    }
    clock_gettime(CLOCK_MONOTONIC, &stop);
    total_time += nano_seconds(&start, &stop);
    
    for (int i = 0; i < loops; i++){
        linked_free(a[i]);
        linked_free(b[i]);
    }
    free(a);
    free(b);

    return (double) total_time/loops;
}


int main(){
    run_benchmark(benchmark_function);
    return 0;
}