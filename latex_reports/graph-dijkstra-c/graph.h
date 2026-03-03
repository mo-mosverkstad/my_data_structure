#pragma once

#include "hashtable.h"

struct graph{
    struct hashtable *nodes;
};

struct graph *graph_fload(char *fname, size_t cap);
void graph_free(struct graph *graph);
void graph_print(struct graph *graph);