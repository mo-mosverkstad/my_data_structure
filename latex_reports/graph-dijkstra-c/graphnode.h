#pragma once
#include <stdbool.h>

struct node{
    char *name;
    struct vec *edges;
};

struct edge{
    struct node *dst;
    int weight;
};

struct node *node_create(char *name);
void node_free(struct node *nd);
bool connect(struct node *src, struct node *dst, int weight);
void print_edge(const void *e);
void node_print(struct node *nd);