// graph_base.c - Implementation of shared graph/hash/CSV for train map assignments
// Build with: gcc -O2 -std=c11 -Wall -Wextra -c graph_base.c
//
// This file provides the core graph data structure and CSV loading functionality.
// Uses hash table for O(1) city lookups and adjacency list for graph representation.

#define _POSIX_C_SOURCE 200809L

#include "graph.h"
#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define LINE_BUF 2048  // Buffer size for reading CSV lines

// Check if string contains only whitespace
static inline int is_space_only(const char *s) {
    if (!s) return 1;
    for (; *s; ++s) if (!isspace((unsigned char)*s)) return 0;
    return 1;
}

static inline void rstrip(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    while (n && isspace((unsigned char)s[n-1])) s[--n] = '\0';
}

static inline void lstrip_inplace(char **ps) {
    if (!ps || !*ps) return;
    unsigned char *p = (unsigned char*)*ps;
    while (*p && isspace(*p)) p++;
    *ps = (char*)p;
}

static inline char *trim(char *s) {
    if (!s) return s;
    rstrip(s);
    lstrip_inplace(&s);
    return s;
}

// Hash function for city names (handles UTF-8 correctly)
// Uses polynomial rolling hash: h = (h * 31 + c) % mod
static unsigned hash_name(const char *name, unsigned mod) {
    unsigned h = 0;
    for (size_t i = 0; name[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)name[i];
        h = (h * 31u + c) % mod;
    }
    return h % mod;
}

// Create new map with specified hash table size
map_t *map_create(int mod) {
    if (mod <= 0) mod = 4099;  // Default for ~100 cities
    map_t *m = (map_t*)calloc(1, sizeof(map_t));
    if (!m) return NULL;
    m->mod = mod;
    m->buckets = (city**)calloc((size_t)mod, sizeof(city*));
    if (!m->buckets) { free(m); return NULL; }
    return m;
}

// Free all memory associated with map
void map_free(map_t *m) {
    if (!m) return;
    for (int b = 0; b < m->mod; ++b) {
        city *c = m->buckets[b];
        while (c) {
            city *nx = c->next_in_bucket;
            // Free adjacency list
            conn *e = c->adj;
            while (e) { conn *enx = e->next; free(e); e = enx; }
            free(c->name);  // Free city name
            free(c);        // Free city structure
            c = nx;
        }
    }
    free(m->buckets);
    free(m);
}

// Look up city by name, optionally create if missing
city *map_lookup(map_t *m, const char *name, int create_if_missing) {
    unsigned h = hash_name(name, (unsigned)m->mod);
    // Search in hash bucket
    for (city *cur = m->buckets[h]; cur; cur = cur->next_in_bucket) {
        if (strcmp(cur->name, name) == 0) return cur;  // Found
    }
    if (!create_if_missing) return NULL;  // Not found

    // Create new city
    city *c = (city*)calloc(1, sizeof(city));
    if (!c) return NULL;
    c->name = strdup(name);
    c->adj  = NULL;
    c->id   = -1;
    c->next_in_bucket = m->buckets[h];  // Insert at head
    m->buckets[h] = c;
    m->city_count++;
    return c;
}

// Add directed edge (or update if exists with minimum distance)
static void connect_directed(city *src, city *dst, int dist) {
    // Check if edge already exists
    for (conn *e = src->adj; e; e = e->next) {
        if (e->dst == dst) { 
            if (dist < e->dist) e->dist = dist;  // Keep minimum
            return; 
        }
    }
    // Create new edge at head of adjacency list
    conn *e = (conn*)malloc(sizeof(conn));
    e->dst = dst; 
    e->dist = dist; 
    e->next = src->adj; 
    src->adj = e;
}

// Add undirected edge (bidirectional)
void connect_undirected(city *a, city *b, int dist) {
    connect_directed(a, b, dist);  // a -> b
    connect_directed(b, a, dist);  // b -> a
}

// String comparison for hashtable
static int cmp_str(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

// Load graph from CSV file (format: src,dst,distance)
// Creates bidirectional edges, uses hashtable for O(1) lookups
//
// Design note: Uses TEMPORARY hashtable during CSV parsing for O(1) city lookups.
// The hashtable is discarded after loading because:
// 1. map_t needs direct bucket access for iteration (Dijkstra, etc.)
// 2. map_t stores city structs directly, not void* pointers
// 3. Hashtable is only needed during loading to avoid O(n) linear searches
map_t *graph_from_csv(const char *file, int mod) {
    // Create TEMPORARY hashtable for fast lookups during parsing
    // This avoids O(n) linear search for each city lookup
    struct hashtable *ht = ht_create((size_t)mod, hash_str, cmp_str);
    if (!ht) return NULL;
    
    map_t *m = map_create(mod);
    if (!m) {
        ht_free(ht);
        return NULL;
    }
    
    FILE *fp = fopen(file, "r");
    if (!fp) {
        ht_free(ht);
        map_free(m);
        return NULL;
    }
    
    char *line = malloc(sizeof(char) * LINE_BUF);
    if (!line) {
        fclose(fp);
        ht_free(ht);
        map_free(m);
        return NULL;
    }
    
    size_t n = LINE_BUF;
    while (getline(&line, &n, fp) > 0) {
        char *src_tok = strtok(line, ",");
        char *dst_tok = strtok(NULL, ",");
        char *dist_tok = strtok(NULL, ",");
        
        if (!src_tok || !dst_tok || !dist_tok) continue;  // Skip invalid
        int dist = atoi(dist_tok);
        
        // Duplicate names (strtok modifies buffer)
        char *src_name = strdup(src_tok);
        char *dst_name = strdup(dst_tok);
        if (!src_name || !dst_name) {
            free(src_name);
            free(dst_name);
            continue;
        }
        
        // Get or create source city
        city *src = ht_get(ht, src_name);
        if (!src) {  // Create new city
            src = (city*)calloc(1, sizeof(city));
            if (!src) {
                free(src_name);
                free(dst_name);
                continue;
            }
            src->name = src_name;  // Take ownership
            src->adj = NULL;
            src->id = m->city_count++;  // Sequential ID
            ht_insert(ht, src_name, src);  // Add to hashtable
            // Add to map's bucket array
            unsigned h = hash_name(src_name, (unsigned)m->mod);
            src->next_in_bucket = m->buckets[h];
            m->buckets[h] = src;
        } else {
            free(src_name);  // City exists, free duplicate
        }
        
        // Get or create destination city (same logic)
        city *dst = ht_get(ht, dst_name);
        if (!dst) {
            dst = (city*)calloc(1, sizeof(city));
            if (!dst) {
                free(dst_name);
                continue;
            }
            dst->name = dst_name;
            dst->adj = NULL;
            dst->id = m->city_count++;
            ht_insert(ht, dst_name, dst);
            unsigned h = hash_name(dst_name, (unsigned)m->mod);
            dst->next_in_bucket = m->buckets[h];
            m->buckets[h] = dst;
        } else {
            free(dst_name);
        }
        
        // Create bidirectional edge
        connect_undirected(src, dst, dist);
        m->edge_count++;
    }
    
    // Cleanup
    free(line);
    fclose(fp);
    ht_free(ht);  // Discard temporary hashtable (no longer needed)
    // map_t keeps its own bucket array for direct iteration access
    return m;
}
