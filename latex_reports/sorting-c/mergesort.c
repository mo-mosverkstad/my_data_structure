#include <stdio.h>
#include <stdlib.h>
#include "arrayutil.h"
#include "merge.h"

void sort(int * org, int * aux, unsigned int lo, unsigned int hi) {
    if (lo < hi) {
        unsigned int mid = lo + (hi - lo) / 2;
        sort(org, aux, lo, mid);
        sort(org, aux, mid + 1, hi);
        copy_array(org, aux, lo, hi + 1);
        merge(org, aux, lo, mid, hi);
    }
}

void mergesort(int * org, unsigned int n) {
    if (org == NULL || n == 0) return;
    int * aux = (int * ) malloc(n * sizeof(int));
    if (!aux) return;
    copy_array(org, aux, 0, n);
    sort(org, aux, 0, n - 1);
    free(aux);
}