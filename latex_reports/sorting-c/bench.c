#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>


void run_benchmark(double benchmark_function(int, void (*)(int*, unsigned int)), void (*sort_func)(int*, unsigned int)) {
    int SIZE_LENGTH = 7;
    int sizes[] = {1024, 2048, 4196, 8192, 16384, 32768, 65535};
    int trials = 16;
    for (int i = 0; i < SIZE_LENGTH; i++) {
        int size = sizes[i];
        double min = DBL_MAX;
        double max = 0;
        double total = 0;
        
        printf("--- BENCHMARK MEASUREMENTS (%d, %d SIZE) ---\n", i, size);
        for (int j = 0; j < trials; j++) {
            double elapsed_time = benchmark_function(size, sort_func);
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