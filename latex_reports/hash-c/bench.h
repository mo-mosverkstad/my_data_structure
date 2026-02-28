#include <time.h>

void run_benchmark(double benchmark_function(int, void (*)(int*, unsigned int)), void (*sort_func)(int*, unsigned int));
long nano_seconds(struct timespec *t_start, struct timespec *t_stop);