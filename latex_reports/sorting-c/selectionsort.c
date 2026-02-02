#include <stdio.h>
#include <stdlib.h>

void selection_sort(int *arr, unsigned int n) {
    if (arr == NULL || n < 2) return;

    for (unsigned int i = 0; i < n - 1; i++) {
        unsigned int min_index = i;
        for (unsigned int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        // swap if a smaller element was found
        if (min_index != i) {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}
