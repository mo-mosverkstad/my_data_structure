#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "vec.h"
#include "hashtable.h"
#include "graphnode.h"
#include "graph.h"

/*
int main() {
    struct node *A = node_create("A");
    struct node *B = node_create("B");
    struct node *C = node_create("C");
    
    connect(A, B, 5);
    connect(A, C, 10);
    connect(B, C, 3);
    
    node_print(A);
    node_print(B);
    node_print(C);
    
    node_free(A);
    node_free(B);
    node_free(C);
}

int main() {
    struct hashtable *ht = ht_create(16, hash_str, cmp_str);

    ht_insert(ht, "apple", "red");
    ht_insert(ht, "banana", "yellow");
    ht_insert(ht, "grape", "purple");
    ht_insert(ht, "lemon", "yellow");
    ht_insert(ht, "lime", "green");

    printf("Hashtable contents:\n");
    ht_print(ht);

    printf("\nGet apple: %s\n", (char *)ht_get(ht, "apple"));
    printf("Get lime: %s\n", (char *)ht_get(ht, "lime"));

    ht_remove(ht, "banana");
    printf("\nAfter removing banana:\n");
    ht_print(ht);

    ht_free(ht);
    return 0;
}
*/


int main(){
    struct graph *my_graph = graph_fload("temp.csv", 27);
    if (!my_graph) {
        printf("ERROR: Failed to load graph\n");
        return 1;
    }
    printf("Loaded CSV graph:\n");
    graph_print(my_graph);
    graph_free(my_graph);
}