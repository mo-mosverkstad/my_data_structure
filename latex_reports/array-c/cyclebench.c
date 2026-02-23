// arrays_bench.c (POSIX)
// Benchmarking arrays operations: clock accuracy, random access, linear search, duplicates
// Based on assignment spec in "Arrays and performance in C" (ID1021, KTH, Spring 2026). 
// Modes: clock | access | search | duplicates
// Build: gcc -O2 -std=c11 arrays_bench.c -o arrays_bench
// Usage examples:
//  ./arrays_bench clock 10
//  ./arrays_bench access 1000 1000 10 > access.csv
//  ./arrays_bench search 1000 1000 10 > search.csv
//  ./arrays_bench duplicates 1000 10 > duplicates.csv


// arrays_bench.c
#define _POSIX_C_SOURCE 199309L   // enable clock_gettime & CLOCK_MONOTONIC

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include <stdint.h>

// Benchmark mechanism 1: Clock nanoseconds
static inline long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) + (t_stop->tv_sec - t_start->tv_sec) * 1000000000L;
}

// Benchmark mechanism 2: CPU cycles (using rdtsc for x86/x64)
static inline uint64_t rdtsc(void) {
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

static inline uint64_t cpu_cycles(uint64_t start, uint64_t stop) {
    return stop - start;
}

static int use_cycles = 0; // 0=nanoseconds, 1=cycles

// CLOCK MODE: print ten consecutive gettime differences
static void mode_clock(int count){
    if(use_cycles){
        for(int i=0;i<count;i++){
            uint64_t start = rdtsc();
            uint64_t stop = rdtsc();
            printf("%lu\n", cpu_cycles(start, stop));
        }
    } else {
        struct timespec t_start, t_stop;
        for(int i=0;i<count;i++){
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            clock_gettime(CLOCK_MONOTONIC, &t_stop);
            long wall = nano_seconds(&t_start, &t_stop);
            printf("%ld\n", wall);
        }
    }
}

// Random access benchmark: returns min wall time over k runs; prints CSV: n,ns_per_op(min)
static uint64_t bench_access_once(int n, int loop){
    int *array = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) array[i] = i;
    int *indx = (int*)malloc(loop * sizeof(int));
    for(int i=0;i<loop;i++) indx[i] = rand() % n;
    volatile int sink = 0;
    uint64_t result;
    if(use_cycles){
        uint64_t start = rdtsc();
        for(int i=0;i<loop;i++) sink += array[indx[i]];
        uint64_t stop = rdtsc();
        result = cpu_cycles(start, stop);
    } else {
        struct timespec t_start, t_stop;
        clock_gettime(CLOCK_MONOTONIC, &t_start);
        for(int i=0;i<loop;i++) sink += array[indx[i]];
        clock_gettime(CLOCK_MONOTONIC, &t_stop);
        result = nano_seconds(&t_start, &t_stop);
    }
    free(array); free(indx);
    if(sink == INT_MIN) fprintf(stderr, "sink: %d\n", sink);
    return result;
}

static void mode_access(int start_n, int loop, int k){
    int sizes[6]; sizes[0]=start_n; for(int i=1;i<6;i++) sizes[i]=sizes[i-1]*2;
    printf("n,%s\n", use_cycles ? "cycles_per_op_min" : "ns_per_op_min");
    for(int s=0;s<6;s++){
        int n = sizes[s];
        uint64_t min = UINT64_MAX;
        for(int i=0;i<k;i++){
            uint64_t result = bench_access_once(n, loop);
            if(result < min) min = result;
        }
        printf("%d,%.2f\n", n, (double)min/loop);
    }
}

// Linear search benchmark: random array of [0,2n), random keys [0,2n)
static uint64_t bench_search_once(int n, int loop){
    int *array = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) array[i] = rand() % (n*2);
    int *keys = (int*)malloc(loop * sizeof(int));
    for(int i=0;i<loop;i++) keys[i] = rand() % (n*2);
    volatile int sink = 0;
    uint64_t result;
    if(use_cycles){
        uint64_t start = rdtsc();
        for(int i=0;i<loop;i++){
            int key = keys[i];
            for(int j=0;j<n;j++){
                if(key == array[j]){ sink++; break; }
            }
        }
        uint64_t stop = rdtsc();
        result = cpu_cycles(start, stop);
    } else {
        struct timespec t_start, t_stop;
        clock_gettime(CLOCK_MONOTONIC, &t_start);
        for(int i=0;i<loop;i++){
            int key = keys[i];
            for(int j=0;j<n;j++){
                if(key == array[j]){ sink++; break; }
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &t_stop);
        result = nano_seconds(&t_start, &t_stop);
    }
    free(array); free(keys);
    if(sink == INT_MIN) fprintf(stderr, "sink: %d\n", sink);
    return result;
}

static void mode_search(int start_n, int loop, int k){
    int sizes[6]; sizes[0]=start_n; for(int i=1;i<6;i++) sizes[i]=sizes[i-1]*2;
    printf("n,%s\n", use_cycles ? "cycles_per_search_min" : "ns_per_search_min");
    for(int s=0;s<6;s++){
        int n = sizes[s];
        uint64_t min = UINT64_MAX;
        for(int i=0;i<k;i++){
            uint64_t result = bench_search_once(n, loop);
            if(result < min) min = result;
        }
        printf("%d,%.2f\n", n, (double)min/loop);
    }
}

// Duplicates benchmark: counts duplicates as described; prints CSV: n,ns_total_min
static uint64_t bench_duplicates_once(int n){
    int *array = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) array[i] = rand() % (n*2);
    volatile int sink = 0;
    uint64_t result;
    if(use_cycles){
        uint64_t start = rdtsc();
        for(int i=0;i<n;i++){
            int key = array[i];
            for(int j=i+1;j<n;j++){
                if(key == array[j]){ sink++; break; }
            }
        }
        uint64_t stop = rdtsc();
        result = cpu_cycles(start, stop);
    } else {
        struct timespec t_start, t_stop;
        clock_gettime(CLOCK_MONOTONIC, &t_start);
        for(int i=0;i<n;i++){
            int key = array[i];
            for(int j=i+1;j<n;j++){
                if(key == array[j]){ sink++; break; }
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &t_stop);
        result = nano_seconds(&t_start, &t_stop);
    }
    free(array);
    if(sink == INT_MIN) fprintf(stderr, "sink: %d\n", sink);
    return result;
}

static void mode_duplicates(int start_n, int k){
    int sizes[6]; sizes[0]=start_n; for(int i=1;i<6;i++) sizes[i]=sizes[i-1]*2;
    printf("n,%s\n", use_cycles ? "cycles_total_min" : "ns_total_min");
    for(int s=0;s<6;s++){
        int n = sizes[s];
        uint64_t min = UINT64_MAX;
        for(int i=0;i<k;i++){
            uint64_t result = bench_duplicates_once(n);
            if(result < min) min = result;
        }
        printf("%d,%lu\n", n, min);
    }
}

int main(int argc, char *argv[]){
    if(argc < 3){
        fprintf(stderr, "Usage: %s <ns|cycles> <mode> [args]\nModes:\n  clock <count>\n  access <start_n> <loop> <k>\n  search <start_n> <loop> <k>\n  duplicates <start_n> <k>\n", argv[0]);
        return 1;
    }
    use_cycles = (strcmp(argv[1], "cycles") == 0);
    srand(42);
    char *mode = argv[2];
    if(strcmp(mode, "clock")==0){
        int count = (argc>=4) ? atoi(argv[3]) : 10;
        mode_clock(count);
        return 0;
    } else if(strcmp(mode, "access")==0){
        if(argc<6){ fprintf(stderr, "access requires <start_n> <loop> <k>\n"); return 1; }
        int start_n = atoi(argv[3]);
        int loop = atoi(argv[4]);
        int k = atoi(argv[5]);
        mode_access(start_n, loop, k);
        return 0;
    } else if(strcmp(mode, "search")==0){
        if(argc<6){ fprintf(stderr, "search requires <start_n> <loop> <k>\n"); return 1; }
        int start_n = atoi(argv[3]);
        int loop = atoi(argv[4]);
        int k = atoi(argv[5]);
        mode_search(start_n, loop, k);
        return 0;
    } else if(strcmp(mode, "duplicates")==0){
        if(argc<5){ fprintf(stderr, "duplicates requires <start_n> <k>\n"); return 1; }
        int start_n = atoi(argv[3]);
        int k = atoi(argv[4]);
        mode_duplicates(start_n, k);
        return 0;
    } else {
        fprintf(stderr, "Unknown mode: %s\n", mode);
        return 1;
    }
}
