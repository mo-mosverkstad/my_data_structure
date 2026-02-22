#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stddef.h>
#include <stdbool.h>

void run_benchmark(void);
void run_benchmark_latex(const char *output_file);
bool binsearch_array(const int *arr, size_t n, int key);

#endif
