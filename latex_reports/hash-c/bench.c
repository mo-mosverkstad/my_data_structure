/**
 * bench.c - Benchmarking utility for performance measurements
 * Provides functions to measure and analyze algorithm performance
 * across different input sizes with statistical analysis
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <float.h>

/**
 * Calculate elapsed time in nanoseconds between two timespec points
 * Returns: elapsed time in nanoseconds
 */
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec- t_start->tv_nsec) + (t_stop->tv_sec- t_start->tv_sec)*1000000000;  // nsec + sec*10^9
}

/**
 * Run benchmark across multiple input sizes with statistical analysis
 * 
 * Parameters:
 *   benchmark_function - Function that runs the benchmark and returns elapsed time
 *   sort_func - The sorting/algorithm function to benchmark
 * 
 * Measures min, max, and average execution times across multiple trials
 */
void run_benchmark(double benchmark_function(int, void (*)(int*, unsigned int)), void (*sort_func)(int*, unsigned int)) {
    int SIZE_LENGTH = 7;
    int sizes[] = {1024, 2048, 4196, 8192, 16384, 32768, 65535};  // Test sizes
    int trials = 16;  // Number of trials per size
    for (int i = 0; i < SIZE_LENGTH; i++) {
        int size = sizes[i];  // Current test size
        double min = DBL_MAX;  // Track minimum time
        double max = 0;  // Track maximum time
        double total = 0;  // Track total time
        
        printf("--- BENCHMARK MEASUREMENTS (%d, %d SIZE) ---\n", i, size);
        for (int j = 0; j < trials; j++) {  // Run multiple trials
            double elapsed_time = benchmark_function(size, sort_func);  // Run benchmark
            if (elapsed_time < min){  // Update minimum
                min = elapsed_time;
            }
            if (elapsed_time > max){  // Update maximum
                max = elapsed_time;
            }
            total += elapsed_time;  // Accumulate total
            printf("ELAPSED TIME PER LOOP: %.2g ns\n", elapsed_time);
        }
        printf("\n");
    
        printf("--- BENCHMARK SUMMARY (%d) ---\n", i);
        printf("MAX TIME: %.2g ns/operation \n", max);
        printf("MIN TIME: %.2g ns/operation \n", min);
        printf("AVG TIME: %.2g ns/operation \n", total/trials);  // Calculate average
        printf("TOT TIME: %.2g ns/operation \n", total);
        printf("\n\n");
    }
}