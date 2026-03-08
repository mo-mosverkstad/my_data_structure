// graph-dfs.c - DFS-based shortest path variants for the train map (graph-c assignment)
// Build: gcc -O2 -std=c11 -Wall -Wextra -o graph-dfs graph-dfs.c graph_base.c
//
// Implements four DFS variants for finding shortest paths:
// 1. dfs-limit: Budget-limited DFS (NO cycle detection - can loop infinitely)
// 2. dfs-limit-Mo: Budget-limited DFS with visited flag (prevents cycles)
// 3. dfs-loop: Path array for cycle detection (no budget, slow)
// 4. dfs-loop-Mo: Path array with budget limit
// 5. dfs-bb: Branch-and-bound with dynamic pruning (fastest)

#define _POSIX_C_SOURCE 200809L

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

// Calculate time difference in nanoseconds
static inline long nano_seconds(const struct timespec *a, const struct timespec *b) {
    long sec = (b->tv_sec - a->tv_sec);
    long ns  = (b->tv_nsec - a->tv_nsec);
    return sec*1000000000L + ns;
}

// ---- DFS 1: Budget-limited DFS (NO cycle detection) ----
// WARNING: Can loop infinitely in bidirectional graphs!
// Only stops when budget runs out, but may revisit same nodes
static int dfs_shortest_limit(city *from, city *to, int left) {
    if (from == to) return 0;  // Reached destination
    int sofar = -1;  // Best distance found (-1 = none)
    // Try all adjacent cities
    for (conn *nxt = from->adj; nxt; nxt = nxt->next) {
        if (nxt->dist <= left) {  // Only if within budget
            // Recurse with reduced budget
            int d = dfs_shortest_limit(nxt->dst, to, left - nxt->dist);
            if (d >= 0) {  // Valid path found
                int cand = d + nxt->dist;  // Total distance
                if (sofar < 0 || cand < sofar) sofar = cand;  // Update best
            }
        }
    }
    return sofar;  // Return best distance or -1
}

// ---- DFS 1: Budget-limited DFS with visited flag (Mo code) ----
// Uses visited flag to prevent cycles - much safer than dfs_shortest_limit
// Complexity: O(b^d) where b=branching factor, d=depth
static int dfs_shortest_visited(city *from, city *to, int left) {
    if (from == to) return 0;  // Base case: reached destination
    if (left < 0) return -1;   // Budget exceeded
    if (from->visited) return -1;  // Cycle detected - already in current path
    
    from->visited = true;  // Mark as visited to prevent cycles
    int sofar = -1;        // Track best distance found
    
    // Try all outgoing edges
    for (conn *nxt = from->adj; nxt; nxt = nxt->next) {
        if (nxt->dist <= left) {  // Only explore if within budget
            // Recursively find path from neighbor to destination
            int d = dfs_shortest_visited(nxt->dst, to, left - nxt->dist);
            if (d >= 0) {  // Valid path found
                int cand = d + nxt->dist;  // Calculate total distance
                if (sofar < 0 || cand < sofar) sofar = cand;  // Update best
            }
        }
    }
    
    from->visited = false;  // Backtrack: unmark for other paths to explore
    return sofar;
}

// ---- DFS 2: Loop-avoiding with path array ----
// Check if city x is already in current path (to detect cycles)
// Complexity: O(k) where k is current path length
static int in_path(city **stk, int k, city *x) {
    for (int i = 0; i < k; ++i) {
        if (stk[i] == x) return 1;  // Found in path - would create cycle
    }
    return 0;  // Not in path - safe to explore
}

// DFS with path array for cycle detection (no budget limit)
// Slower than visited flag due to O(k) loop check on every edge
static int dfs_shortest_loop(city *from, city *to, city **path, int k) {
    if (from == to) return 0;  // Reached destination
    int sofar = -1;  // Best distance found
    
    // Try all adjacent cities
    for (conn *nxt = from->adj; nxt; nxt = nxt->next) {
        if (!in_path(path, k, nxt->dst)) {  // Only if not in current path
            path[k] = nxt->dst;  // Add to path
            int d = dfs_shortest_loop(nxt->dst, to, path, k+1);  // Recurse
            if (d >= 0) {
                int cand = d + nxt->dist;
                if (sofar < 0 || cand < sofar) sofar = cand;
            }
            // Note: path[k] automatically "removed" when we return
        }
    }
    return sofar;
}

// ---- DFS 2: Loop-avoiding with budget (Mo code) ----
/*
 * DFS with path array to track visited nodes AND budget limit
 * 
 * Algorithm: Uses path array instead of visited flag to prevent loops
 * 
 * Why it's slow:
 * - The in_path() function checks the entire path array on every edge exploration
 * - O(k) time complexity for each loop check, where k is the current path length
 * - Path array checking is more expensive than visited flag (O(1))
 * - Total complexity: O(b^d * d) where b=branching, d=depth
 * 
 * Performance: ~15-40ms for long routes (vs ~0.01ms for dfs-limit-Mo)
 */
static int dfs_shortest_loop_budget(city *from, city *to, city **path, int k, int remaining) {
    if (from == to) return 0;  // Base case: reached destination
    if (remaining < 0) return -1;  // Budget exceeded
    
    int best = -1;  // Track best distance found
    
    // Try all outgoing edges
    for (conn *e = from->adj; e; e = e->next) {
        // Only explore if: (1) not in current path AND (2) within budget
        if (!in_path(path, k, e->dst) && e->dist <= remaining) {
            path[k] = e->dst;  // Add to path
            // Recurse with reduced budget
            int d = dfs_shortest_loop_budget(e->dst, to, path, k+1, remaining - e->dist);
            if (d >= 0) {
                int cand = d + e->dist;
                if (best < 0 || cand < best) best = cand;  // Update best distance
            }
        }
    }
    return best;
}


// ---- DFS 3: Branch-and-bound with dynamic pruning (FASTEST) ----
/*
 * Key optimization: Pass best_so_far down the recursion tree
 * Prunes branches that cannot possibly beat current best solution
 * 
 * Example: If best path found so far is 500 minutes, and current edge
 * costs 600 minutes, skip it entirely - can't possibly improve.
 * 
 * Performance: ~0.01-4ms for long routes (50-100x faster than dfs-loop)
 * Complexity: Still O(b^d) worst case, but dramatically reduced in practice
 */
static int dfs_bb_inner(city *from, city *to, city **path, int k, int best_so_far) {
    if (from == to) return 0;  // Reached destination
    
    int sofar = best_so_far;  // Current best bound
    int found = 0;  // Track if we found any valid path
    
    // Try all adjacent cities
    for (conn *nxt = from->adj; nxt; nxt = nxt->next) {
        // Skip if: (1) already in path (cycle) OR (2) edge alone exceeds bound
        if (in_path(path, k, nxt->dst)) continue;  // Avoid cycles
        if (sofar >= 0 && nxt->dist >= sofar) continue;  // ⭐ PRUNING!
        
        path[k] = nxt->dst;  // Add to path
        // Recurse with updated bound (remaining budget for subtree)
        int d = dfs_bb_inner(nxt->dst, to, path, k+1,
                             sofar < 0 ? -1 : (sofar - nxt->dist));
        if (d >= 0) {  // Valid path found
            int cand = d + nxt->dist;
            if (sofar < 0 || cand < sofar) { 
                sofar = cand;  // Update bound
                found = 1; 
            }
        }
    }
    return found ? sofar : -1;  // Return best or -1 if no path
}

// Wrapper to start branch-and-bound search
static int dfs_shortest_bb(city *from, city *to, city **path, int k) {
    return dfs_bb_inner(from, to, path, k, -1);  // Start with no bound
}

// Print usage information
static void usage(const char *p) {
    fprintf(stderr,
        "usage:\n"
        "  %s -f <csv> -a dfs-limit <from> <to> <budget_minutes>\n"
        "  %s -f <csv> -a dfs-limit-Mo <from> <to> <budget_minutes>\n"
        "  %s -f <csv> -a dfs-loop  <from> <to>\n"
        "  %s -f <csv> -a dfs-loop-Mo <from> <to> <budget_minutes>\n"
        "  %s -f <csv> -a dfs-bb    <from> <to>\n", p, p, p, p, p);
}

int main(int argc, char **argv) {
    // Parse command line arguments
    const char *csv = NULL; 
    const char *algo = NULL; 
    int i = 1; 
    int mod = 4099;  // Hash table size
    
    for (; i < argc; ++i) {
        if (strcmp(argv[i], "-f") == 0 && i+1 < argc) csv = argv[++i];
        else if (strcmp(argv[i], "-a") == 0 && i+1 < argc) algo = argv[++i];
        else if (strcmp(argv[i], "-mod") == 0 && i+1 < argc) mod = atoi(argv[++i]);
        else break;  // Non-option argument
    }
    
    // Validate required arguments
    if (!csv || !algo) { usage(argv[0]); return 1; }
    if (i+1 >= argc) { usage(argv[0]); return 1; }
    
    char *from_name = argv[i++];
    char *to_name   = argv[i++];

    // Load graph from CSV
    map_t *m = graph_from_csv(csv, mod);
    if (!m) return 1;

    // Look up source and destination cities
    city *from = map_lookup(m, from_name, 0);
    city *to   = map_lookup(m, to_name,   0);
    if (!from || !to) {
        fprintf(stderr, "unknown city: %s%s%s\n",
                !from ? from_name : "", (!from && !to) ? " and " : "",
                !to   ? to_name   : "");
        map_free(m); 
        return 2;
    }

    struct timespec t0, t1;
    int ans = -1;

    // Execute selected algorithm and measure time
    if (strcmp(algo, "dfs-limit") == 0) {
        // Budget-limited DFS (NO cycle detection - can loop!)
        if (i >= argc) { usage(argv[0]); map_free(m); return 1; }
        int budget = atoi(argv[i++]);
        clock_gettime(CLOCK_MONOTONIC, &t0);
        ans = dfs_shortest_limit(from, to, budget);
        clock_gettime(CLOCK_MONOTONIC, &t1);
    } else if (strcmp(algo, "dfs-limit-Mo") == 0) {
        // Budget-limited DFS with visited flag (safe)
        if (i >= argc) { usage(argv[0]); map_free(m); return 1; }
        int budget = atoi(argv[i++]);
        clock_gettime(CLOCK_MONOTONIC, &t0);
        ans = dfs_shortest_visited(from, to, budget);
        clock_gettime(CLOCK_MONOTONIC, &t1);
    } else if (strcmp(algo, "dfs-loop") == 0) {
        // Path array for cycle detection (no budget)
        city **path = (city**)calloc((size_t)m->city_count, sizeof(city*));
        path[0] = from;  // Initialize with source
        clock_gettime(CLOCK_MONOTONIC, &t0);
        ans = dfs_shortest_loop(from, to, path, 1);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        free(path);
    } else if (strcmp(algo, "dfs-loop-Mo") == 0) {
        // Path array with budget limit
        if (i >= argc) { usage(argv[0]); map_free(m); return 1; }
        int budget = atoi(argv[i++]);
        city **path = (city**)calloc((size_t)m->city_count, sizeof(city*));
        path[0] = from;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        ans = dfs_shortest_loop_budget(from, to, path, 1, budget);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        free(path);
    } else if (strcmp(algo, "dfs-bb") == 0) {
        // Branch-and-bound with dynamic pruning (fastest)
        city **path = (city**)calloc((size_t)m->city_count, sizeof(city*));
        path[0] = from;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        ans = dfs_shortest_bb(from, to, path, 1);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        free(path);
    } else { 
        usage(argv[0]); 
        map_free(m); 
        return 1; 
    }

    // Calculate elapsed time in nanoseconds
    long ns = t1.tv_sec*1000000000L + t1.tv_nsec - (t0.tv_sec*1000000000L + t0.tv_nsec);

    // Print results
    if (ans >= 0) 
        printf("[%s] from %s to %s: shortest %d minutes (%.2f us)\n", 
               algo, from_name, to_name, ans, (double)ns/1e3);
    else          
        printf("[%s] from %s to %s: no path found (%.2f us)\n", 
               algo, from_name, to_name, (double)ns/1e3);

    map_free(m);
    return 0;
}
