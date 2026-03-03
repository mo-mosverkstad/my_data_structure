#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "graphnode.h"

#define BUFFER 64

int cmp_str(const void *a, const void *b) {
    return strcmp((const char *) a, (const char *) b);
}

struct graph{
    struct hashtable *nodes;
};

// graph_fload: graph file load, fname: file name, NULL for failed load
// TODO: Clean allocated resources whenever allocation/operation fails and return an error message
// TODO: Trim string if needed
struct graph *graph_fload(char *fname, size_t cap, bool double_linked) { 
    struct hashtable *nodes_ht = ht_create(cap, hash_str, cmp_str);
    if (!nodes_ht) return NULL;
    struct graph *graph = (struct graph *) malloc(sizeof(struct graph));
    if (!graph){
        free(nodes_ht);
        return NULL;
    }
    graph->nodes = nodes_ht;
    
    FILE *fptr = fopen(fname, "r");
    if (fptr == NULL){
        free(nodes_ht);
        free(graph);
        return NULL;
    }
    char *lineptr = (char *) malloc(sizeof(char) * BUFFER);
    if (!lineptr){
        fclose(fptr);
        free(nodes_ht);
        free(graph);
        return NULL;
    }
    size_t n = BUFFER;
    while (getline(&lineptr, &n, fptr) > 0) {
        char *src_tok = strtok(lineptr, ",");
        char *dst_tok = strtok(NULL, ",");
        int weight = atoi(strtok(NULL, ","));
    
        if (!src_tok || !dst_tok) break;
    
        char *src_name = strdup(src_tok);
        char *dst_name = strdup(dst_tok);
        if (!src_name || !dst_name) break;
        
        struct node *src = ht_get(nodes_ht, src_name);
        if (!src) {
            src = node_create(src_name);
            if (!src) break;
            ht_insert(nodes_ht, src_name, src);
        } else {
            free(src_name);
        }
    
        struct node *dst = ht_get(nodes_ht, dst_name);
        if (!dst) {
            dst = node_create(dst_name);
            if (!dst) break;
            ht_insert(nodes_ht, dst_name, dst);
        } else {
            free(dst_name);
        }
    
        connect(src, dst, weight);
        if (double_linked) connect(dst, src, weight);
    }
    free(lineptr);
    fclose(fptr);
    return graph;
}

void free_node_cb(void *key, void *value){
    free(key); // free name as char array
    node_free((struct node *) value); // free value as node
}

void graph_free(struct graph *graph){
    if (!graph) return;

    ht_foreach(graph->nodes, free_node_cb);
    ht_free(graph->nodes);
    free(graph);
}

void graph_print_cb(void *key, void *value){
    printf("  (\"%s\", %p)\n", (char *)key, value);
}

void graph_print(struct graph *graph){
    printf("Graph{\n");
    ht_foreach(graph->nodes, graph_print_cb);
    printf("}\n");
}