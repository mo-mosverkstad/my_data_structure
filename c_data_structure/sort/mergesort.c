#include <stdio.h>
#include <stdlib.h>

void print_array(int * arr, int n) {
    printf("[");
    if (n > 0)
        for (int i = 0; i < n - 1; i++)
            printf("%d, ", arr[i]);
    printf("%d]", arr[n - 1]);
}

void copy_array(int * src, int * dest, int start, int end) {
    for (int i = start; i < end; i++)
        dest[i] = src[i];
}

void merge(int * org, int * aux, int lo, int mid, int hi) {
    int i = lo;
    int j = mid + 1;
    for (int k = lo; k <= hi; k++) {
        if (i > mid)
            org[k] = aux[j++];
        else if (j > hi)
            org[k] = aux[i++];
        else if (aux[i] <= aux[j])
            org[k] = aux[i++];
        else
            org[k] = aux[j++];
    }
}

void sort(int * org, int * aux, int lo, int hi) {
    if (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        sort(org, aux, lo, mid);
        sort(org, aux, mid + 1, hi);
        copy_array(org, aux, lo, hi + 1);
        merge(org, aux, lo, mid, hi);
    }
}

void mergesort(int * org, int n) {
    if (n == 0) return;
    int * aux = (int * ) malloc(n * sizeof(int));
    copy_array(org, aux, 0, n);
    sort(org, aux, 0, n - 1);
}

int main(){
    int arr[] = {124, 817, 273, 848, 298, 737, 372, 653, 201, 2736, 273, 3283, 212, 1, 23, 9773, 9, 5, 1, 1245, 2312, 32, 123, 252};
    mergesort(arr, 24);
    print_array(arr, 24);
    return 0;
}