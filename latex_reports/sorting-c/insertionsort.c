#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int *arr, unsigned int n){
    if (arr == NULL || n == 0) return;
    for (unsigned int i = 1; i < n; i++) {
        int hole_element = arr[i];
        unsigned int j = i;
        while (j > 0 && arr[j-1] > hole_element) {
            arr[j] = arr[j-1];
            j--;
        }
        arr[j] = hole_element;
    }
}
