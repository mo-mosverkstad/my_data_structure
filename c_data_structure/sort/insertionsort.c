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

void insertion_sort(int *arr, int n){
    for (int i = 1; i < n; i++){
        int hole_index = i;
        int hole_element = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > hole_element){
            arr[j + 1] = arr[j];
            hole_index = j;
            j--;
        }
        arr[hole_index] = hole_element;
    }
}

int main(){
    int arr[] = {124, 817, 273, 848, 298, 737, 372, 653, 201, 2736, 273, 3283, 212, 1, 23, 9773, 9, 5, 1, 1245, 2312, 32, 123, 252};
    insertion_sort(arr, sizeof(arr)/sizeof(int));
    print_array(arr, sizeof(arr)/sizeof(int));
    return 0;
}