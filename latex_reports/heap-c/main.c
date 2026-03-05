#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "list_pq1.h"
#include "list_pq2.h"
#include "bst_heap.h"
#include "tree_heap.h"
#include "array_heap.h"

static inline long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) + (t_stop->tv_sec - t_start->tv_sec) * 1000000000L;
}

void benchmark_heap(void* (*create)(unsigned int), bool (*enqueue)(void*, int), 
                    bool (*dequeue)(void*, int*), void (*free_heap)(void*), const char* name){
    int sizes[] = {1024, 2048, 4096, 8192, 16384, 32768, 65536};
    
    for (int s = 0; s < 7; s++){
        int size = sizes[s];
        int* data = malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) data[i] = rand();
        
        double min_enqueue = LONG_MAX, min_dequeue = LONG_MAX;
        
        for (int trial = 0; trial < 3; trial++){
            void* h = create(size);
            struct timespec t_start, t_stop;
            int result;
            
            // Measure enqueue on full queue
            long total_enqueue = 0;
            for (int i = 0; i < size; i++) enqueue(h, data[i]);  // Fill queue first
            for (int i = 0; i < size; i++) {
                dequeue(h, &result);  // Remove one
                clock_gettime(CLOCK_MONOTONIC, &t_start);
                enqueue(h, data[i]);  // Add one back (queue stays at size-1 to size)
                clock_gettime(CLOCK_MONOTONIC, &t_stop);
                total_enqueue += nano_seconds(&t_start, &t_stop);
            }
            double enqueue_time = (double)total_enqueue / size;
            if (enqueue_time < min_enqueue) min_enqueue = enqueue_time;
            
            // Refill to full size for dequeue measurement
            while (dequeue(h, &result));
            for (int i = 0; i < size; i++) enqueue(h, data[i]);
            
            // Measure dequeue on full queue
            long total_dequeue = 0;
            for (int i = 0; i < size; i++) {
                clock_gettime(CLOCK_MONOTONIC, &t_start);
                dequeue(h, &result);
                clock_gettime(CLOCK_MONOTONIC, &t_stop);
                total_dequeue += nano_seconds(&t_start, &t_stop);
                enqueue(h, data[i]);  // Refill after dequeue to maintain size
            }
            double dequeue_time = (double)total_dequeue / size;
            if (dequeue_time < min_dequeue) min_dequeue = dequeue_time;
            
            free_heap(h);
        }
        
        printf("%s [%d]: Enqueue %.2f ns, Dequeue %.2f ns\n", name, size, min_enqueue, min_dequeue);
        free(data);
    }
}

void benchmark_pq1(){
    benchmark_heap((void*(*)(unsigned int))list_pq1_create, 
                   (bool(*)(void*, int))list_pq1_enqueue,
                   (bool(*)(void*, int*))list_pq1_dequeue,
                   (void(*)(void*))list_pq1_free, "PQ1");
}

void benchmark_pq2(){
    benchmark_heap((void*(*)(unsigned int))list_pq2_create,
                   (bool(*)(void*, int))list_pq2_enqueue,
                   (bool(*)(void*, int*))list_pq2_dequeue,
                   (void(*)(void*))list_pq2_free, "PQ2");
}

void benchmark_ah(){
    benchmark_heap((void*(*)(unsigned int))create_array_heap,
                   (bool(*)(void*, int))array_heap_enqueue,
                   (bool(*)(void*, int*))array_heap_dequeue,
                   (void(*)(void*))free_array_heap, "Array Heap");
}

static void* bst_create_wrapper(unsigned int cap){
    (void)cap;
    return construct_bst_tree();
}

static void* tree_heap_create_wrapper(unsigned int cap){
    (void)cap;
    return create_heap();
}

void benchmark_bst(){
    benchmark_heap(bst_create_wrapper,
                   (bool(*)(void*, int))bst_heap_enqueue,
                   (bool(*)(void*, int*))bst_heap_dequeue,
                   (void(*)(void*))free_bst_tree, "BST Heap");
}

void benchmark_tree_heap(){
    benchmark_heap(tree_heap_create_wrapper,
                   (bool(*)(void*, int))tree_heap_enqueue,
                   (bool(*)(void*, int*))tree_heap_dequeue,
                   (void(*)(void*))free_heap, "Tree Heap");
}

void benchmark_push() {
    heap *hp1 = create_heap();
    for (int i = 0; i < 1023; i++) {
        tree_heap_enqueue(hp1, rand() % 10001);
    }
    
    int total_depth1 = 0, max_depth1 = 0, ops = 1000;
    long min_time1 = LONG_MAX;
    struct timespec t_start, t_stop;
    
    for (int i = 0; i < ops; i++) {
        clock_gettime(CLOCK_MONOTONIC, &t_start);
        int depth = push(hp1, 10 + rand() % 91);
        clock_gettime(CLOCK_MONOTONIC, &t_stop);
        long elapsed = nano_seconds(&t_start, &t_stop);
        if (elapsed < min_time1) min_time1 = elapsed;
        total_depth1 += depth;
        if (depth > max_depth1) max_depth1 = depth;
    }
    
    printf("Direct push:\n  Avg depth: %.2f\n  Max depth: %d\n  Min time: %ld ns\n", 
           (double)total_depth1 / ops, max_depth1, min_time1);
    free_heap(hp1);
    
    heap *hp2 = create_heap();
    for (int i = 0; i < 1023; i++) {
        tree_heap_enqueue(hp2, rand() % 10001);
    }
    
    int total_depth2 = 0, max_depth2 = 0;
    long min_time2 = LONG_MAX;
    for (int i = 0; i < ops; i++) {
        int val;
        clock_gettime(CLOCK_MONOTONIC, &t_start);
        tree_heap_dequeue(hp2, &val);
        int depth = tree_heap_enqueue_depth(hp2, val + 10 + rand() % 91);
        clock_gettime(CLOCK_MONOTONIC, &t_stop);
        long elapsed = nano_seconds(&t_start, &t_stop);
        if (elapsed < min_time2) min_time2 = elapsed;
        total_depth2 += depth;
        if (depth > max_depth2) max_depth2 = depth;
    }
    
    printf("Dequeue-enqueue:\n  Avg depth: %.2f\n  Max depth: %d\n  Min time: %ld ns\n", 
           (double)total_depth2 / ops, max_depth2, min_time2);
    free_heap(hp2);
}

void benchmark_bst_skew() {
    int sizes[] = {1024, 2048, 4096, 8192, 16384, 32768, 65536};
    
    for (int s = 0; s < 7; s++) {
        int size = sizes[s];
        int* data = malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) data[i] = rand();
        
        bst_tree *tree = construct_bst_tree();
        
        // Create balanced BST by inserting sorted values in balanced order
        for (int i = 0; i < size; i++) {
            bst_heap_enqueue(tree, data[i]);
        }
        
        struct timespec t_start, t_stop;
        long total_enqueue = 0, total_dequeue = 0;
        
        // Dequeue min, enqueue larger - causes right skew
        for (int i = 0; i < size; i++) {
            int val;
            
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            bst_heap_dequeue(tree, &val);
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            total_dequeue += nano_seconds(&t_start, &t_stop);
            
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            bst_heap_enqueue(tree, val + rand() % 100);
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            total_enqueue += nano_seconds(&t_start, &t_stop);
        }
        
        printf("BST Skew [%d]: Enqueue %.2f ns, Dequeue %.2f ns\n", 
               size, (double)total_enqueue / size, (double)total_dequeue / size);
        
        free_bst_tree(tree);
        free(data);
    }
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    if (argc > 1 && strcmp(argv[1], "--lpq1") == 0){
        benchmark_pq1();
    }
    else if (argc > 1 && strcmp(argv[1], "--lpq2") == 0){
        benchmark_pq2();
    }
    else if (argc > 1 && strcmp(argv[1], "--ah") == 0){
        benchmark_ah();
    }
    else if (argc > 1 && strcmp(argv[1], "--bst") == 0){
        benchmark_bst();
    }
    else if (argc > 1 && strcmp(argv[1], "--bst-skew") == 0){
        benchmark_bst_skew();
    }
    else if (argc > 1 && strcmp(argv[1], "--th") == 0){
        benchmark_tree_heap();
    }
    else if (argc > 1 && strcmp(argv[1], "--push") == 0){
        benchmark_push();
    }
}