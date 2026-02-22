#define _POSIX_C_SOURCE 200809L
#include "benchmark.h"
#include "tree.h"
#include "latex_output.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

static int *make_range(size_t n) {
    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) { perror("malloc range"); exit(EXIT_FAILURE); }
    for (size_t i = 0; i < n; ++i) arr[i] = (int)i;
    return arr;
}

static void shuffle(int *arr, size_t n) {
    for (size_t i = n; i > 1; --i) {
        size_t j = (size_t) (rand() % i);
        int tmp = arr[i - 1];
        arr[i - 1] = arr[j];
        arr[j] = tmp;
    }
}

static long nanoseconds(struct timespec a, struct timespec b) {
    long sec = (long) (b.tv_sec - a.tv_sec);
    long nsec = (long) (b.tv_nsec - a.tv_nsec);
    return sec * 1000000000L + nsec;
}

bool binsearch_array(const int *arr, size_t n, int key) {
    /* Binary search with arithmetic overhead:
     * - Computes mid = lo + (hi - lo) / 2 each iteration (4 operations)
     * - Updates lo/hi bounds (additional arithmetic)
     * - Random memory access pattern causes cache misses
     * Result: Often SLOWER than balanced BST despite same O(log N) complexity
     */
    size_t lo = 0, hi = n;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;  /* Arithmetic overhead */
        int v = arr[mid];
        if (key == v) return true;
        if (key < v) hi = mid;
        else lo = mid + 1;
    }
    return false;
}

static long calculate_time(void (*work_func)(void*), void *context, size_t repeat, void (*cleanup_func)(void*)) {
    struct timespec t0, t1;
    long min_time = LONG_MAX;
    for (size_t count = 0; count < repeat; ++count) {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        work_func(context);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        long elapsed = nanoseconds(t0, t1);
        if (elapsed < min_time) min_time = elapsed;
        if (cleanup_func) cleanup_func(context);
    }
    return min_time;
}

typedef struct {
    tree *tr;
    int *vals;
    size_t N;
    void (*add_func)(tree*, int);
} build_context;

typedef struct {
    const tree *tr;
    int *vals;
    size_t N;
} lookup_context;

typedef struct {
    const int *arr_sorted;
    size_t arr_size;  /* Size of the sorted array */
    int *vals;        /* Search keys */
    size_t num_vals;  /* Number of search keys */
} binsearch_context;

static void do_build(void *ctx) {
    build_context *bc = (build_context*)ctx;
    for (size_t i = 0; i < bc->N; ++i)
        bc->add_func(bc->tr, bc->vals[i]);
}

static void cleanup_build(void *ctx) {
    build_context *bc = (build_context*)ctx;
    free_node(bc->tr->root);
    bc->tr->root = NULL;
}

static void do_lookup(void *ctx) {
    lookup_context *lc = (lookup_context*)ctx;
    for (size_t i = 0; i < lc->N; ++i)
        tree_lookup_iterative(lc->tr, lc->vals[i]);
}

static void do_binsearch(void *ctx) {
    binsearch_context *bc = (binsearch_context*)ctx;
    for (size_t i = 0; i < bc->num_vals; ++i)
        binsearch_array(bc->arr_sorted, bc->arr_size, bc->vals[i]);
}

static long benchmark_build(tree *tr, int *vals, size_t N, size_t repeat, void (*add_func)(tree*, int)) {
    build_context ctx = {tr, vals, N, add_func};
    return calculate_time(do_build, &ctx, repeat, cleanup_build);
}

static long benchmark_lookup(const tree *tr, int *vals, size_t N, size_t repeat) {
    lookup_context ctx = {tr, vals, N};
    return calculate_time(do_lookup, &ctx, repeat, NULL);
}

static long benchmark_binsearch(const int *arr_sorted, size_t arr_size, int *vals, size_t num_vals, size_t repeat) {
    binsearch_context ctx = {arr_sorted, arr_size, vals, num_vals};
    return calculate_time(do_binsearch, &ctx, repeat, NULL);
}

static void build_balanced_bst(tree *tr, int *sorted, int left, int right) {
    if (left > right) return;
    int mid = left + (right - left) / 2;
    add(tr, sorted[mid]);
    build_balanced_bst(tr, sorted, left, mid - 1);
    build_balanced_bst(tr, sorted, mid + 1, right);
}

void run_benchmark_common(const char *latex_output) {
    size_t sizes[] = {1024, 2048, 4096, 8192, 16384, 32768, 65535, 131072};
    size_t nsizes = sizeof(sizes) / sizeof(sizes[0]);
    size_t repeat = 10;
    size_t num_lookups = 1024;  /* Fixed number of lookups for consistent measurement */
    long build_rec[8], build_iter[8], lookup_balanced[8], lookup_shuffled[8], lookup_unbalanced[8], lookup_arr[8];

    if (latex_output) printf("Running benchmarks for LaTeX output...\n");
    /*
    printf(latex_output ? "[Build benchmarks]\n" : "=== BUILD BENCHMARK ===\n");
    if (!latex_output) printf("Columns: N | build_ns(rec) | build_ns(iter)\n");

    for (size_t s = 0; s < nsizes; ++s) {
        if (latex_output) { printf("  [%zu/%zu] N=%zu", s+1, nsizes, sizes[s]); fflush(stdout); }
        int *vals = make_range(sizes[s]);
        shuffle(vals, sizes[s]);
        tree *tr_rec = construct_tree();
        build_rec[s] = benchmark_build(tr_rec, vals, sizes[s], repeat, recursive_add);
        tree *tr_it = construct_tree();
        build_iter[s] = benchmark_build(tr_it, vals, sizes[s], repeat, add);
        if (!latex_output) printf("%7zu | %13ld | %14ld\n", sizes[s], build_rec[s], build_iter[s]);
        free_tree(tr_rec); free_tree(tr_it); free(vals);
        if (latex_output) printf(" ✓\n");
    }
    */
   
    printf(latex_output ? "[Lookup benchmarks]\n" : "\n=== LOOKUP BENCHMARK ===\n");
    if (!latex_output) printf("Columns: N | balanced | shuffled | unbalanced | binsearch\n");

    for (size_t s = 0; s < nsizes; ++s) {
        if (latex_output) { printf("  [%zu/%zu] N=%zu", s+1, nsizes, sizes[s]); fflush(stdout); }
        
        int *sorted = make_range(sizes[s]);
        int *shuffled = make_range(sizes[s]);
        shuffle(shuffled, sizes[s]);
        
        /* Generate search keys distributed across the entire range */
        int *search_keys = malloc(num_lookups * sizeof(int));
        for (size_t i = 0; i < num_lookups; ++i) {
            search_keys[i] = rand() % sizes[s];  /* Random keys in [0, N) */
        }
        
        /* Balanced BST */
        tree *tr_balanced = construct_tree();
        build_balanced_bst(tr_balanced, sorted, 0, sizes[s] - 1);
        long total_balanced = benchmark_lookup(tr_balanced, search_keys, num_lookups, repeat);
        lookup_balanced[s] = total_balanced / num_lookups;
        
        /* Shuffled BST */
        tree *tr_shuffled = construct_tree();
        for (size_t i = 0; i < sizes[s]; ++i) add(tr_shuffled, shuffled[i]);
        long total_shuffled = benchmark_lookup(tr_shuffled, search_keys, num_lookups, repeat);
        lookup_shuffled[s] = total_shuffled / num_lookups;
        
        /* Unbalanced BST (sorted insertion) */
        tree *tr_unbalanced = construct_tree();
        for (size_t i = 0; i < sizes[s]; ++i) add(tr_unbalanced, sorted[i]);
        long total_unbalanced = benchmark_lookup(tr_unbalanced, search_keys, num_lookups, repeat);
        lookup_unbalanced[s] = total_unbalanced / num_lookups;
        
        /* Binary search on sorted array */
        long total_arr = benchmark_binsearch(sorted, sizes[s], search_keys, num_lookups, repeat);
        lookup_arr[s] = total_arr / num_lookups;
        
        if (!latex_output) {
            printf("%7zu | %8ld | %8ld | %10ld | %9ld\n", 
                   sizes[s], lookup_balanced[s], lookup_shuffled[s], lookup_unbalanced[s], lookup_arr[s]);
        }
        
        free(sorted); free(shuffled); free(search_keys);
        free_tree(tr_balanced); free_tree(tr_shuffled); free_tree(tr_unbalanced);
        if (latex_output) printf(" ✓\n");
    }

    if (latex_output) {
        printf("[Writing LaTeX output]\n");
        output_latex(latex_output, sizes, nsizes, build_rec, build_iter, lookup_balanced, lookup_shuffled, lookup_unbalanced, lookup_arr);
        printf("LaTeX output written to %s ✓\n", latex_output);
    }
}

void run_benchmark(void) {
    run_benchmark_common(NULL);
}

void run_benchmark_latex(const char *output_file) {
    run_benchmark_common(output_file);
}
