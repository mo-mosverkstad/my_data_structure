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

/*
int main(int argc, char* argv[]) {
    map *trains = graph("trains.csv");
    if(argc < 4) {
        printf("usage: %s <from> <to> <limit>\n", argv[0]);
        return 1;
    }
    city *from = lookup(trains, argv[1]);
    city *to = lookup(trains, argv[2]);
    int limit = atoi(argv[3]);
    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    int s = search(from, to, limit);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    if (s > 0)
        printf("shortest path %d found in %.2fms\n", s, ((double)wall)/1000000);
    else
        printf("no path found\n");
}
*/


int shortest(struct node *src, struct node *dst, int remaining) {
    if (src == dst) {
        return 0;
    }
    char *next = "<NONE>";
    int sofar = -1;
    struct vec *edges = src->edges;
    for (unsigned int i = 0; i < edges->len; i++){
        struct edge *edge = vec_get(edges, i);
        if (edge->weight <= remaining){
            int d = shortest(edge->dst, dst, remaining - edge->weight);
            if (d >= 0 && ((sofar == -1) || (d + edge->weight < sofar))){
                sofar = d + edge->weight;
                next = edge->dst->name;
            }
        }
    }
    printf("Next: %s\n", next);
    return sofar;
}

int main(){
    struct graph *my_graph = graph_fload("temp.csv", 27);
    if (!my_graph) {
        printf("ERROR: Failed to load graph\n");
        return 1;
    }
    struct node *src = ht_get(my_graph->nodes, "Telefonplan");
    struct node *dst = ht_get(my_graph->nodes, "Bromma");
    if (!src){
        printf("ERROR: Invalid source\n");
        return 1;
    }
    if (!dst){
        printf("ERROR: Invalid destination\n");
        return 1;
    }
    int limit = 17000;
    
    printf("Loaded CSV graph:\n");
    graph_print(my_graph);
    
    printf("\n");
    
    int s = shortest(src, dst, limit);
    printf("s = %d\n", s);
    
    graph_free(my_graph);
}