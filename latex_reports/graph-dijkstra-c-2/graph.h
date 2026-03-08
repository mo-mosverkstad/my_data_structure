// graph.h - Shared graph types and API for the train map assignments
// Encoding: UTF-8
// This header declares a simple adjacency-list graph stored in a hash table.
// Hash function uses unsigned char per assignment guidance to handle UTF-8 bytes correctly.
//
// Design: map_t maintains its own hash table (buckets array) for direct access.
// A temporary generic hashtable is used during CSV loading for O(1) lookups,
// then discarded. This avoids O(n) linear searches during graph construction.

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct city city;
typedef struct conn conn;

typedef struct {
    city       **buckets;    // hash table buckets
    int          mod;        // table size (prime recommended)
    int          city_count; // number of cities when initialization to allocate memory
    long         edge_count; // number of undirected edges added when initialization to allocate memory
} map_t;

struct city {
    char  *name;             // UTF-8 city name (bytewise compare)
    conn  *adj;              // adjacency list
    int    id;               // compact index (0..city_count-1)
    bool visited;            // true if visited during search
    city  *next_in_bucket;   // next in hash chain
};

struct conn {
    city *dst;
    int   dist;              // minutes (positive integer)
    conn *next;
};


// ---- Map / Hash API ----
map_t *map_create(int mod);
void   map_free(map_t *m);

// Lookup city by name; if create_if_missing != 0, create a new city on demand.
city * map_lookup(map_t *m, const char *name, int create_if_missing);

// Add undirected connection (both directions). If edge already exists, keep the minimum distance.
void   connect_undirected(city *a, city *b, int dist);

// Load a graph from CSV file (lines: from,to,minutes[,]).
// The parser is whitespace tolerant and ignores an extra trailing comma.
map_t *graph_from_csv(const char *file, int mod);

#ifdef __cplusplus
}
#endif

#endif // GRAPH_H
