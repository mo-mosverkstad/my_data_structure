// graph-dijkstra.c - Dijkstra shortest path for the train map (graph-dijkstra-c assignment)
// Build: gcc -O2 -std=c11 -Wall -Wextra -o graph-dijkstra graph-dijkstra.c graph_base.c

#define _POSIX_C_SOURCE 200809L

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

// --- path structure as per assignment ---
typedef struct path {
    city *city;
    city *prev;
    int dist;
} path;

// --- priority queue for paths (min-heap based on distance) ---
typedef struct pq {
    path *a;    // dynamic array of path entries (heap storage)
    int n;      // current number of elements in heap
    int cap;    // allocated capacity of array
} PriorityQueue;

// Create new priority queue with initial capacity
static PriorityQueue *pq_new(int cap) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->n = 0;
    pq->cap = cap > 0 ? cap : 64;
    pq->a = (path*)malloc((size_t)pq->cap * sizeof(path));
    return pq;
}

// Free priority queue and its internal array
static void pq_free(PriorityQueue *pq) {
    if (pq) {
        free(pq->a);
        free(pq);
    }
}

// Insert path into priority queue (min-heap by distance)
// Automatically grows array if needed, then bubbles up to maintain heap property
static void pq_push(PriorityQueue *pq, city *c, city *prev, int dist) {
    // Grow array if full
    if (pq->n == pq->cap) {
        pq->cap *= 2;
        pq->a = (path*)realloc(pq->a, (size_t)pq->cap * sizeof(path));
    }
    // Add new element at end
    int i = pq->n++;
    pq->a[i].city = c;
    pq->a[i].prev = prev;
    pq->a[i].dist = dist;
    // Bubble up to maintain min-heap property
    while (i > 0) {
        int p = (i - 1) / 2;  // parent index
        if (pq->a[p].dist <= pq->a[i].dist) break;
        path t = pq->a[p];
        pq->a[p] = pq->a[i];
        pq->a[i] = t;
        i = p;
    }
}

// Extract minimum (shortest distance) path from priority queue
// Returns 1 if successful, 0 if queue is empty
// After removal, bubbles down to restore heap property
static int pq_pop(PriorityQueue *pq, path *out) {
    if (pq->n == 0) return 0;  // empty queue
    *out = pq->a[0];  // return minimum element
    pq->a[0] = pq->a[--pq->n];  // move last element to root
    // Bubble down to restore min-heap property
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;  // left, right, minimum
        if (l < pq->n && pq->a[l].dist < pq->a[m].dist) m = l;
        if (r < pq->n && pq->a[r].dist < pq->a[m].dist) m = r;
        if (m == i) break;  // heap property satisfied
        path t = pq->a[i];
        pq->a[i] = pq->a[m];
        pq->a[m] = t;
        i = m;
    }
    return 1;
}

static inline long ns_between(const struct timespec *a, const struct timespec *b) {
    long sec = (b->tv_sec - a->tv_sec);
    long ns  = (b->tv_nsec - a->tv_nsec);
    return sec*1000000000L + ns;
}

// Initialize done[] array - all cities unvisited
static path *init_done_array(int n) {
    path *done = (path*)calloc((size_t)n, sizeof(path));
    for (int i = 0; i < n; ++i) {
        done[i].city = NULL;  // NULL means not visited
        done[i].prev = NULL;
        done[i].dist = INT_MAX;
    }
    return done;
}

// Relax edges: explore all neighbors of current city and add to queue
static void relax_neighbors(city *c, path *current, path *done, PriorityQueue *pq) {
    for (conn *e = c->adj; e; e = e->next) {
        city *neighbor = e->dst;
        // Only explore unvisited neighbors
        if (done[neighbor->id].city == NULL) {
            int new_dist = current->dist + e->dist;
            pq_push(pq, neighbor, c, new_dist);
        }
    }
}

// Dijkstra's shortest path algorithm
// Finds shortest path from src to dst, stores visited cities in done[] array
// Returns distance to destination, or -1 if no path exists
static int dijkstra(map_t *m, city *src, city *dst, path **done_out, int *done_count) {
    int n = m->city_count;
    path *done = init_done_array(n);
    
    PriorityQueue *pq = pq_new(n * 2);
    pq_push(pq, src, NULL, 0);
    
    int visited = 0;
    path current;
    
    while (pq_pop(pq, &current)) {
        city *c = current.city;
        
        // Early termination: destination reached
        if (c == dst) {
            done[c->id] = current;
            visited++;
            pq_free(pq);
            if (done_out) *done_out = done;
            else free(done);
            if (done_count) *done_count = visited;
            return current.dist;
        }
        
        // Skip stale entries (already visited)
        if (done[c->id].city == NULL) {
            done[c->id] = current;
            visited++;
            relax_neighbors(c, &current, done, pq);
        }
    }
    
    // No path found
    pq_free(pq);
    if (done_out) *done_out = done;
    else free(done);
    if (done_count) *done_count = visited;
    return -1;
}

static char **reconstruct(city *src, city *dst, path *done, int *out_n) {
    int cap = 16, k = 0;
    city **stk = (city**)malloc((size_t)cap * sizeof(city*));
    city *cur = dst;
    
    // Walk backward from destination to source
    while (cur) {
        if (k == cap) {
            cap *= 2;
            stk = (city**)realloc(stk, (size_t)cap * sizeof(city*));
        }
        stk[k++] = cur;
        if (cur == src) break;
        cur = done[cur->id].prev;
    }
    
    if (!cur) {
        free(stk);
        *out_n = 0;
        return NULL;
    }
    
    // Reverse to get path from source to destination
    char **names = (char**)malloc((size_t)k * sizeof(char*));
    for (int i = 0; i < k; ++i) {
        names[i] = stk[k - 1 - i]->name;
    }
    free(stk);
    *out_n = k;
    return names;
}

static void usage(const char *p) {
    fprintf(stderr,
        "usage:\n"
        "  %s -f <csv> <from> <to> [-p] [-mod <prime>]\n", p);
}

int main(int argc, char **argv) {
    const char *csv=NULL; int i=1; int print_path=0; int mod=4099;
    for(; i<argc; ++i){
        if(strcmp(argv[i],"-f")==0 && i+1<argc) csv=argv[++i];
        else if(strcmp(argv[i],"-p")==0) print_path=1;
        else if(strcmp(argv[i],"-mod")==0 && i+1<argc) mod=atoi(argv[++i]);
        else break;
    }
    if(!csv || i+1>=argc){ usage(argv[0]); return 1; }
    char *from_name=argv[i++]; char *to_name=argv[i++];

    map_t *m = graph_from_csv(csv, mod);
    if(!m) return 1;

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    
    city *from = map_lookup(m, from_name, 0);
    city *to   = map_lookup(m, to_name, 0);
    
    clock_gettime(CLOCK_MONOTONIC, &t1);
    long lookup_ns = ns_between(&t0, &t1);
    
    if(!from || !to){ 
        fprintf(stderr, "unknown city: %s%s%s (%.2f us)\n", 
                !from?from_name:"", (!from&&!to)?" and ":"", !to?to_name:"", (double)lookup_ns/1e3); 
        map_free(m); 
        return 2; 
    }

    clock_gettime(CLOCK_MONOTONIC, &t0);
    
    path *done = NULL;
    int done_count = 0;
    int ans = dijkstra(m, from, to, &done, &done_count);
    
    clock_gettime(CLOCK_MONOTONIC, &t1);
    long ns = ns_between(&t0, &t1);

    if (ans >= 0) {
        printf("[dijkstra] shortest %d minutes (%.2f us)\n", ans, (double)ns / 1e3);
        printf("cities visited: %d\n", done_count);
        if (print_path) {
            int n = 0;
            char **names = reconstruct(from, to, done, &n);
            if (names) {
                printf("path: ");
                for (int j = 0; j < n; ++j) {
                    if (j) printf(" -> ");
                    printf("%s", names[j]);
                }
                printf("\n");
                free(names);
            }
        }
    } else {
        printf("[dijkstra] no path found (%.2f us)\n", (double)ns / 1e3);
        printf("cities visited: %d\n", done_count);
    }

    free(done);
    map_free(m);
    return 0;
}
