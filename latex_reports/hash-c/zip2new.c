#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define AREAS 10000
#define BUFFER 200

typedef struct area {
    char *name;
    int zip;
    int pop;
} area;

typedef struct codes {
    area *areas;
    int n;
} codes;

codes *read_postcodes(const char *file) {
    codes *post = malloc(sizeof(codes));
    area *arr = malloc(sizeof(area) * AREAS);

    FILE *f = fopen(file, "r");
    if (!f) { printf("Could not open %s\n", file); exit(1); }

    char *line = malloc(BUFFER);
    size_t n = BUFFER;
    int k = 0;

    while (k < AREAS && getline(&line, &n, f) > 0) {
        char *copy = malloc(n);
        strcpy(copy, line);

        char *zip = strtok(copy, ",");
        char *name = strtok(NULL, ",");
        char *pop_str = strtok(NULL, ",");

        arr[k].zip = atoi(zip) * 100 + atoi(zip + 3);
        arr[k].name = strdup(name);
        arr[k].pop = atoi(pop_str);

        k++;
    }

    fclose(f);
    post->areas = arr;
    post->n = k;
    return post;
}

int linear_lookup(codes *c, int key) {
    for (int i = 0; i < c->n; i++)
        if (c->areas[i].zip == key)
            return i;
    return -1;
}

int binary_lookup(codes *c, int key) {
    int L = 0, R = c->n - 1;
    while (L <= R) {
        int mid = (L + R) / 2;
        int z = c->areas[mid].zip;
        if (z == key) return mid;
        else if (key < z) R = mid - 1;
        else L = mid + 1;
    }
    return -1;
}

static inline long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) + (t_stop->tv_sec - t_start->tv_sec) * 1000000000L;
}

void bench(const char *name, int (*func)(codes*, int), codes *c, int key) {
    struct timespec t_start, t_stop;
    long min = LONG_MAX;
    int r;
    for (int i = 0; i < 1024; i++) {
        clock_gettime(CLOCK_MONOTONIC, &t_start);
        r = func(c, key);
        clock_gettime(CLOCK_MONOTONIC, &t_stop);
        long t = nano_seconds(&t_start, &t_stop);
        if (t < min) min = t;
    }
    printf("%s: key=%d result=%d time=%.1f ns\n",
        name, key, r, (float)min);
}

int main() {
    codes *post = read_postcodes("zipcodes.csv");

    int a = 11115;
    int b = 98499;

    printf("=== Linear vs Binary ===\n");
    bench("Linear", linear_lookup, post, a);
    bench("Linear", linear_lookup, post, b);
    bench("Binary", binary_lookup, post, a);
    bench("Binary", binary_lookup, post, b);

    return 0;
}
