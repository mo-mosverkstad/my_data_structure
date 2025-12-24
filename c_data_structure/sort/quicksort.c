#include <stdio.h>
#include <stdlib.h>

void print_array(int * arr, int n) {
    printf("[");
    if (n > 0)
        for (int i = 0; i < n - 1; i++)
            printf("%d, ", arr[i]);
    printf("%d]", arr[n - 1]);
}

void quick_sort(int *arr, int start, int end){
    if (start >= end) return;
    if (end - start <= 1) return;
    int pivot_index = (start + end)/2;
    int pivot_value = arr[pivot_index];
    int i = start;
    int j = end - 1;
    while (i < j){
        while (arr[i] < pivot_value) i++;
        while (arr[j] > pivot_value) j--;
        if (i < j){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    quick_sort(arr, start, i);
    quick_sort(arr, i, end);
}

int main(){
    // int arr[] = {124, 817, 273, 848, 298, 737, 372, 653, 201, 2736, 273, 3283, 212, 1, 23, 9773, 9, 5, 1, 1245, 2312, 32, 123, 252};
    int arr[] = {124, 123, 32, 1, 5, 9, 23, 1, 201, 212, 273, 3283, 2736, 653, 372, 9773, 737, 298, 848, 1245, 2312, 273, 817, 252};
    quick_sort(arr, 0, sizeof(arr)/sizeof(int));
    print_array(arr, sizeof(arr)/sizeof(int));
    return 0;
}