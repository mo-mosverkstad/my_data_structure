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

void selection_sort(int *arr, int n){
    for (int i = 0; i < n; i++){
        int min_index = i;
        for (int j = i+1; j < n; j++){
            if (arr[j] < arr[min_index]){
                min_index = j;
            }
        }
        if (min_index != i){
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

int main(){
    int arr[] = {124, 817, 273, 848, 298, 737, 372, 653, 201, 2736, 273, 3283, 212, 1, 23, 9773, 9, 5, 1, 1245, 2312, 32, 123, 252};
    selection_sort(arr, sizeof(arr) / sizeof(int));
    print_array(arr, sizeof(arr) / sizeof(int));
    return 0;
}