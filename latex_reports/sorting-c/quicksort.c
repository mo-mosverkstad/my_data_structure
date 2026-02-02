#include <stdio.h>
#include <stdlib.h>

void quick_sort_inner(int *arr, unsigned int start, unsigned int end){
    if (start >= end) return;
    if (end - start <= 1) return;
    unsigned int pivot_index = (start + end)/2;
    int pivot_value = arr[pivot_index];
    unsigned int i = start;
    unsigned int j = end - 1;
    while (i < j){
        while (arr[i] < pivot_value && i < end) i++;
        while (arr[j] > pivot_value && j > start) j--;
        if (i < j){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    quick_sort_inner(arr, start, i);
    quick_sort_inner(arr, i, end);
}

void quick_sort_inner(int *arr, unsigned int start, unsigned int end) {
    if (end - start <= 1) return;
    unsigned int pivot_index = start + (end - start) / 2;
    int pivot_value = arr[pivot_index];
    unsigned int i = start;
    unsigned int j = end - 1;

    while (i <= j) {
        while (i < end && arr[i] < pivot_value) i++;
        while (j > start && arr[j] > pivot_value) j--;

        if (i <= j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            if (j > 0) j--;
        }
    }

    quick_sort_inner(arr, start, j + 1);
    quick_sort_inner(arr, i, end);
}


void quicksort(int *arr, unsigned int n){
    if (arr == NULL || n == 0) return;
    quick_sort_inner(arr, 0, n);
}