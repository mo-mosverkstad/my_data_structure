#include <stdio.h>
#include <stdlib.h>

void print_array(int * arr, unsigned int n) {
    printf("[");
    if (n > 0){
        for (unsigned int i = 0; i < n - 1; i++)
            printf("%d, ", arr[i]);
        printf("%d", arr[n - 1]);
    }
    printf("]");
}

void copy_array(int * src, int * dest, unsigned int start, unsigned int end) {
    for (unsigned int i = start; i < end; i++)
        dest[i] = src[i];
}