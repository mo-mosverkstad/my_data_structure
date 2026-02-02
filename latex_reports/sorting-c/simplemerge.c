#include <stdio.h>
#include <stdlib.h>
#include "arrayutil.h"
#include "merge.h"

void simple_mergesort_inner(int * org, int * aux, unsigned int lo, unsigned int hi) {
    if (lo < hi) {
        unsigned int mid = lo + (hi - lo) / 2;
        simple_mergesort_inner(aux, org, lo, mid);
        simple_mergesort_inner(aux, org, mid + 1, hi);
        merge(org, aux, lo, mid, hi);
    }
}

void simple_mergesort(int * org, unsigned int n) {
    if (org == NULL || n == 0) return;
    int * aux = (int * ) malloc(n * sizeof(int));
    if (!aux) return;
    copy_array(org, aux, 0, n);
    simple_mergesort_inner(org, aux, 0, n - 1);
    free(aux);
}