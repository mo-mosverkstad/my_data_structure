#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "vec.h"

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
    nd->name = strdup(name);
    nd->edges = vec_create(sizeof(struct edge));
    if (!nd->edges){
        free(nd);
        return NULL;
    }
    return nd;
}

void node_free(struct node *nd){
    if (!nd) return;
    free(nd->name);
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