#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vec.h"
#include "hashtable.h"

// graph node

struct node{
    char *name;
    struct vec *edges;
};

struct edge{
    struct node *dst;
    int weight;
};

// true for successful operation, false for failed operation
struct node *node_create(char *name){
    struct node *nd = (struct node *) malloc(sizeof(struct node));
    if (!nd) return NULL;
    nd->name = name;
    nd->edges = vec_create(sizeof(struct edge));
    if (!nd->edges){
        free(nd);
        return NULL;
    }
    return nd;
}

void node_free(struct node *nd){
    if (!nd) return;
    vec_free(nd->edges);
    free(nd);
}

// true for successful operation, false for failed operation
bool connect(struct node *src, struct node *dst, int weight){
    struct edge e;
    e.dst = dst;
    e.weight = weight;
    return vec_append(src->edges, &e);
}

void print_edge(const void *e){
    const struct edge *edge = (const struct edge *)e;
    printf("(%s, %d)", edge->dst->name, edge->weight);
}

void node_print(struct node *nd){
    printf("Node(%s): ", nd->name);
    vec_print(nd->edges, print_edge);
}

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
*/

int cmp_str(const void *a, const void *b) {
    return strcmp((const char *) a, (const char *) b);
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