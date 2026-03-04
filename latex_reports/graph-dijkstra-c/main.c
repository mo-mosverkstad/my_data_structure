#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "vec.h"
#include "hashtable.h"
#include "graphnode.h"
#include "graph.h"
#include "priorityqueue.h"

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

// naive impl 1
int shortest(struct node *src, struct node *dst, int remaining) {
    if (src == dst) {
        return 0;
    }
    // if (src->visited) return -1;
    // src->visited = true;
    // char *next = "<NONE>";
    int sofar = -1;
    struct vec *edges = src->edges;
    for (unsigned int i = 0; i < edges->len; i++){
        struct edge *edge = vec_get(edges, i);
        if (edge->weight <= remaining){
            int d = shortest(edge->dst, dst, remaining - edge->weight);
            if (d >= 0 && ((sofar == -1) || (d + edge->weight < sofar))){
                sofar = d + edge->weight;
                // next = edge->dst->name;
            }
        }
    }
    src->visited = false;
    // printf("Next: %s\n", next);
    return sofar;
}

// helper function
bool loop(struct node *path[], int k, struct node *n) {
    for (int i = 0; i < k; i++) {
        if (path[i] == n) return true;
    }
    return false;
}

// naive impl 2
int shortest_path(struct node *src, struct node *dst, struct node *path[], int k){
    if (src == dst) return 0;
    int sofar = -1;
    struct vec *edges = src->edges;
    for (unsigned int i = 0; i < edges->len; i++) {
        struct edge *edge = vec_get(edges, i);
        if (!loop(path, k, edge->dst)) {
            path[k] = edge->dst;
            int d = shortest_path(edge->dst, dst, path, k + 1);
            if (d >= 0 && (sofar == -1 || d + edge->weight < sofar)) {
                sofar = d + edge->weight;
            }
        }
    }
    return sofar;
}

// helpers to Dijkstra's algorithm
struct path {
    struct node *node;
    int weight;
    struct node *prev;
};

int path_cmp(const void *a, const void *b) {
    const struct path *pa = (const struct path *) a;
    const struct path *pb = (const struct path *) b;
    return pa->weight - pb->weight;
}

// Dijkstra's algorithm
struct path **dijkstra(struct node *src, struct node *dst, int n_nodes){
    struct priority_queue *pq = pq_create(n_nodes, path_cmp);
    if (!pq) return NULL;
    struct path **done = calloc(n_nodes, sizeof(struct path *));
    if (!done) {
        pq_free(pq);
        return NULL;
    }

    struct path *start = (struct path *) malloc(sizeof(struct path));
    start->node = src;
    start->weight = 0;
    start->prev = NULL;
    pq_enqueue(pq, start);
    while (pq->size > 0) {
        struct path *current;
        pq_dequeue(pq, (void **) &current);
        int id = current->node->id;

        if (done[id] == NULL){
            done[id] = current;
            // destination reached?
            if (current->node == dst) break;
            // expand neighbours
            struct vec *edges = current->node->edges;
            for (unsigned int i = 0; i < edges->len; i++) {
                struct edge *e = (struct edge *) vec_get(edges, i);
                if (done[e->dst->id] != NULL) continue;
                struct path *new_path = malloc(sizeof(struct path));
                new_path->node = e->dst;
                new_path->weight = current->weight + e->weight;
                new_path->prev = current->node;

                pq_enqueue(pq, new_path);
            }
        }
        else{
            free(current);
        }
    }
    pq_free(pq);
    return done;  // dst unreachable
}

void print_shortest_path(struct path **done, struct node *dst){
    struct path *p = done[dst->id];
    if (!p) {
        printf("No path found\n");
        return;
    }

    printf("Distance: %d\nPath: ", p->weight);

    // Build path in reverse
    struct node *path[256];
    int len = 0;
    while (p) {
        path[len++] = p->node;
        if (!p->prev)
            break;
        p = done[p->prev->id];
    }

    // Print path forward
    for (int i = len - 1; i >= 0; i--) {
        printf("%s", path[i]->name);
        if (i > 0) printf(" -> ");
    }

    printf("\n");
}

int naive_test(){
    // configs
    
    /*
    char *fname = "temp.csv";
    int ht_size = 27;
    char *src_name = "Telefonplan";
    char *dst_name = "Bromma";
    bool doubly_linked = true;
    int limit = 11000;
    */

    /*
    char *fname = "europe.csv";
    int ht_size = 259;
    char *src_name = "Göteborg";
    char *dst_name = "Malmö";
    bool doubly_linked = true;
    int limit = 200;
    */
    
    char *fname = "temp.csv";
    int ht_size = 27;
    char *src_name = "Bromma";
    char *dst_name = "Telefonplan";
    bool doubly_linked = true;

    // implementation
    struct graph *my_graph = graph_fload(fname, ht_size, doubly_linked);
    if (!my_graph) {
        printf("ERROR: Failed to load graph\n");
        return 1;
    }
    struct node *src = ht_get(my_graph->nodes, src_name);
    struct node *dst = ht_get(my_graph->nodes, dst_name);
    if (!src){
        printf("ERROR: Invalid source\n");
        return 1;
    }
    if (!dst){
        printf("ERROR: Invalid destination\n");
        return 1;
    }
    
    printf("Loaded CSV graph:\n");
    graph_print(my_graph);
    
    printf("\n");
    
    // int s = shortest(src, dst, limit);
    
    const unsigned int path_size = 16;
    struct node *path[path_size];
    path[0] = src;
    int s = shortest_path(src, dst, path, 1);
    printf("s = %d\n", s);
    
    graph_free(my_graph);
    return 0;
}

int dijkstra_test(){
    // small driving road map
    char *fname = "temp.csv";
    int ht_size = 27;
    char *src_name = "Bromma";
    char *dst_name = "KTH Campus D-E-building";
    bool doubly_linked = true;

    struct graph *my_graph = graph_fload(fname, ht_size, doubly_linked);
    if (!my_graph) {
        printf("ERROR: Failed to load graph\n");
        return 1;
    }
    
    struct node *src = ht_get(my_graph->nodes, src_name);
    struct node *dst = ht_get(my_graph->nodes, dst_name);
    if (!src){
        printf("ERROR: Invalid source\n");
        return 1;
    }
    if (!dst){
        printf("ERROR: Invalid destination\n");
        return 1;
    }
    
    printf("Loaded CSV graph:\n");
    graph_print(my_graph);
    printf("\n");
    
    // Assign unique IDs to all nodes
    int node_count = 0;
    struct hashtable *ht = my_graph->nodes;
    for (size_t i = 0; i < ht->cap; i++) {
        struct entry *entry = ht->buckets[i];
        while (entry) {
            struct node *n = (struct node *)entry->value;
            n->id = node_count++;
            entry = entry->next;
        }
    }
    
    // Run Dijkstra's algorithm
    struct path **done = dijkstra(src, dst, node_count);
    
    if (done) {
        printf("Shortest path from %s to %s:\n", src_name, dst_name);
        print_shortest_path(done, dst);
        
        // Free the done array
        for (int i = 0; i < node_count; i++) {
            if (done[i]) free(done[i]);
        }
        free(done);
    } else {
        printf("ERROR: Dijkstra failed\n");
    }
    
    graph_free(my_graph);
    return 0;
}

int main(){
    return dijkstra_test();
}