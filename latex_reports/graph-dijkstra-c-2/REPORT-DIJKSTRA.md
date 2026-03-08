# Graphs in C — Dijkstra Assignment Report

**Dataset:** `trains.csv` (Sweden). **52 nodes**, **75 undirected links**.

**Goal:** Implement Dijkstra's algorithm to compute shortest paths with non-negative edge weights, with path reconstruction and timing.

---

## 1. Algorithm & Data Structures

### Data Structures (per assignment specification):

**city** structure:
```c
typedef struct city {
    char *name;
    int id;              // numbered 0 to n-1 for array indexing
    conn *adj;           // adjacency list of neighbors
    city *next_in_bucket;
} city;
```

**path** structure:
```c
typedef struct path {
    city *city;  // current city
    city *prev;  // previous city on path
    int dist;    // total distance from origin
} path;
```

**done[]** array:
- Stores shortest known path to each visited city
- Indexed by city ID
- Contains path entries with distance and previous city
- Used to reconstruct full route by walking backward

**Priority Queue**:
- Min-heap storing path entries
- Always expands shortest known path first
- Compares paths by distance

### Dijkstra's Algorithm Process:

1. Remove shortest path from queue
2. If path ends at destination → done
3. If first time encountering this city:
   - Place path in done[] array
   - Expand: add all neighbors to queue with updated distances

**Complexity:** O((V + E) log V) with binary heap

---

## 2. Usage

```bash
make
./graph-dijkstra -f trains.csv "Malmö" "Göteborg" -p
./graph-dijkstra -f trains.csv "Stockholm" "Umeå" -p
```

**Example outputs (ground truth for the dataset):**

- Malmö → Göteborg: 153 minutes; path: Malmö → Lund → Åstorp → Halmstad → Varberg → Göteborg
- Göteborg → Stockholm: 211 minutes; path: Göteborg → Herrljunga → Falköping → Skövde → Hallsberg → Katrineholm → Södertälje → Stockholm
- Malmö → Stockholm: 273 minutes (path via Hässleholm → Alvesta → Nässjö → …)
- Stockholm → Sundsvall: 327 minutes (via Uppsala → Gävle)
- Stockholm → Umeå: 517 minutes (via Uppsala → Gävle → Sundsvall)
- Göteborg → Sundsvall: 515 minutes (via Herrljunga → Falköping → … → Gävle)
- Sundsvall → Umeå: 190 minutes

---

## 3. Why Dijkstra Beats DFS Here

- DFS explores **paths**, re-visiting same subproblems many times; combinatorial explosion even with loop detection
- Dijkstra explores **frontiers** by increasing distance, **remembers** best distances in done[] array
- Each city expanded exactly once → avoids repeated work
- Output shows "cities visited" count = entries in done[] array

---

## 4. Implementation Details

**Key features:**
- path struct with city, prev, and dist fields
- done[] array tracks visited cities and shortest paths
- Priority queue of path entries (min-heap on distance)
- Path reconstruction walks backward through done[] array
- Reports cities visited (done[] entries) for benchmarking

**Files:**
- `graph.h`, `graph_base.c` - shared graph structures
- `graph-dijkstra.c` - Dijkstra implementation per assignment spec
- `trains.csv` - 52 nodes, 75 undirected edges




## 5. Benchmark and results
========================================
Testing DFS-LIMIT (with budget)
========================================
[dfs-limit] from Malmö to Göteborg: shortest 153 minutes (0.33 ms)
[dfs-limit] from Göteborg to Stockholm: shortest 211 minutes (485.20 ms)
[TIMEOUT] ./graph-dfs -f trains.csv -a dfs-limit Malmö Stockholm 700
[dfs-limit] from Stockholm to Sundsvall: shortest 327 minutes (343.18 ms)
[TIMEOUT] ./graph-dfs -f trains.csv -a dfs-limit Stockholm Umeå 1200
[TIMEOUT] ./graph-dfs -f trains.csv -a dfs-limit Göteborg Sundsvall 1000
[dfs-limit] from Sundsvall to Umeå: shortest 190 minutes (0.00 ms)
[TIMEOUT] ./graph-dfs -f trains.csv -a dfs-limit Umeå Göteborg 1200
[TIMEOUT] ./graph-dfs -f trains.csv -a dfs-limit Göteborg Umeå 1200

========================================
Testing DFS-LIMIT-Mo (with budget and visited flag)
========================================
[dfs-limit-Mo] from Malmö to Göteborg: shortest 153 minutes (0.00 ms)
[dfs-limit-Mo] from Göteborg to Stockholm: shortest 211 minutes (0.07 ms)
[dfs-limit-Mo] from Malmö to Stockholm: shortest 273 minutes (0.44 ms)
[dfs-limit-Mo] from Stockholm to Sundsvall: shortest 327 minutes (0.11 ms)
[dfs-limit-Mo] from Stockholm to Umeå: shortest 517 minutes (9.99 ms)
[dfs-limit-Mo] from Göteborg to Sundsvall: shortest 515 minutes (5.13 ms)
[dfs-limit-Mo] from Sundsvall to Umeå: shortest 190 minutes (0.00 ms)
[dfs-limit-Mo] from Umeå to Göteborg: shortest 705 minutes (2.26 ms)
[dfs-limit-Mo] from Göteborg to Umeå: shortest 705 minutes (11.73 ms)

========================================
Testing DFS-LOOP (loop-avoiding)
========================================
[dfs-loop] from Malmö to Göteborg: shortest 153 minutes (226.21 ms)
[dfs-loop] from Göteborg to Stockholm: shortest 211 minutes (117.29 ms)
[dfs-loop] from Malmö to Stockholm: shortest 273 minutes (229.07 ms)
[dfs-loop] from Stockholm to Sundsvall: shortest 327 minutes (167.06 ms)
[dfs-loop] from Stockholm to Umeå: shortest 517 minutes (222.82 ms)
[dfs-loop] from Göteborg to Sundsvall: shortest 515 minutes (207.31 ms)
[dfs-loop] from Sundsvall to Umeå: shortest 190 minutes (594.78 ms)
[dfs-loop] from Umeå to Göteborg: shortest 705 minutes (240.58 ms)
[dfs-loop] from Göteborg to Umeå: shortest 705 minutes (253.77 ms)

========================================
Testing DFS-LOOP-Mo (loop-avoiding with budget)
========================================
[dfs-loop-Mo] from Malmö to Göteborg: shortest 153 minutes (0.01 ms)
[dfs-loop-Mo] from Göteborg to Stockholm: shortest 211 minutes (0.16 ms)
[dfs-loop-Mo] from Malmö to Stockholm: shortest 273 minutes (1.51 ms)
[dfs-loop-Mo] from Stockholm to Sundsvall: shortest 327 minutes (0.26 ms)
[dfs-loop-Mo] from Stockholm to Umeå: shortest 517 minutes (47.48 ms)
[dfs-loop-Mo] from Göteborg to Sundsvall: shortest 515 minutes (19.14 ms)
[dfs-loop-Mo] from Sundsvall to Umeå: shortest 190 minutes (0.00 ms)
[dfs-loop-Mo] from Umeå to Göteborg: shortest 705 minutes (7.13 ms)
[dfs-loop-Mo] from Göteborg to Umeå: shortest 705 minutes (49.57 ms)

========================================
Testing DFS-BB (branch-and-bound)
========================================
[dfs-bb] from Malmö to Göteborg: shortest 153 minutes (0.01 ms)
[dfs-bb] from Göteborg to Stockholm: shortest 211 minutes (0.03 ms)
[dfs-bb] from Malmö to Stockholm: shortest 273 minutes (0.05 ms)
[dfs-bb] from Stockholm to Sundsvall: shortest 327 minutes (0.07 ms)
[dfs-bb] from Stockholm to Umeå: shortest 517 minutes (0.67 ms)
[dfs-bb] from Göteborg to Sundsvall: shortest 515 minutes (0.78 ms)
[dfs-bb] from Sundsvall to Umeå: shortest 190 minutes (0.00 ms)
[dfs-bb] from Umeå to Göteborg: shortest 705 minutes (0.10 ms)
[dfs-bb] from Göteborg to Umeå: shortest 705 minutes (4.47 ms)

========================================
Testing Dijkstra
========================================
[dijkstra] shortest 153 minutes (0.00 ms)
cities visited: 14
[dijkstra] shortest 211 minutes (0.00 ms)
cities visited: 32
[dijkstra] shortest 273 minutes (0.00 ms)
cities visited: 30
[dijkstra] shortest 327 minutes (0.01 ms)
cities visited: 44
[dijkstra] shortest 517 minutes (0.01 ms)
cities visited: 48
[dijkstra] shortest 515 minutes (0.01 ms)
cities visited: 46
[dijkstra] shortest 190 minutes (0.00 ms)
cities visited: 4
[dijkstra] shortest 705 minutes (0.00 ms)
cities visited: 36
[dijkstra] shortest 705 minutes (0.01 ms)
cities visited: 48

2nd us:
./test_routes.sh
========================================
Testing DFS-LIMIT (with budget)
========================================
[dfs-limit] from Malmö to Göteborg: shortest 153 minutes (315.37 us)
[dfs-limit] from Göteborg to Stockholm: shortest 211 minutes (734595.32 us)
[TIMEOUT] ./graph-dfs -f trains.csv -a dfs-limit Malmö Stockholm 700
[dfs-limit] from Stockholm to Sundsvall: shortest 327 minutes (350657.28 us)
[TIMEOUT] ./graph-dfs -f trains.csv -a dfs-limit Stockholm Umeå 1200
[TIMEOUT] ./graph-dfs -f trains.csv -a dfs-limit Göteborg Sundsvall 1000
[dfs-limit] from Sundsvall to Umeå: shortest 190 minutes (3.62 us)
[TIMEOUT] ./graph-dfs -f trains.csv -a dfs-limit Umeå Göteborg 1200
[TIMEOUT] ./graph-dfs -f trains.csv -a dfs-limit Göteborg Umeå 1200

========================================
Testing DFS-LIMIT-Mo (with budget and visited flag)
========================================
[dfs-limit-Mo] from Malmö to Göteborg: shortest 153 minutes (5.50 us)
[dfs-limit-Mo] from Göteborg to Stockholm: shortest 211 minutes (77.25 us)
[dfs-limit-Mo] from Malmö to Stockholm: shortest 273 minutes (563.48 us)
[dfs-limit-Mo] from Stockholm to Sundsvall: shortest 327 minutes (119.70 us)
[dfs-limit-Mo] from Stockholm to Umeå: shortest 517 minutes (13580.18 us)
[dfs-limit-Mo] from Göteborg to Sundsvall: shortest 515 minutes (4788.36 us)
[dfs-limit-Mo] from Sundsvall to Umeå: shortest 190 minutes (0.56 us)
[dfs-limit-Mo] from Umeå to Göteborg: shortest 705 minutes (1843.75 us)
[dfs-limit-Mo] from Göteborg to Umeå: shortest 705 minutes (13499.44 us)

========================================
Testing DFS-LOOP (loop-avoiding)
========================================
[dfs-loop] from Malmö to Göteborg: shortest 153 minutes (203800.11 us)
[dfs-loop] from Göteborg to Stockholm: shortest 211 minutes (99446.35 us)
[dfs-loop] from Malmö to Stockholm: shortest 273 minutes (207679.89 us)
[dfs-loop] from Stockholm to Sundsvall: shortest 327 minutes (167049.47 us)
[dfs-loop] from Stockholm to Umeå: shortest 517 minutes (244151.65 us)
[dfs-loop] from Göteborg to Sundsvall: shortest 515 minutes (197677.96 us)
[dfs-loop] from Sundsvall to Umeå: shortest 190 minutes (540183.07 us)
[dfs-loop] from Umeå to Göteborg: shortest 705 minutes (173291.64 us)
[dfs-loop] from Göteborg to Umeå: shortest 705 minutes (255146.37 us)

========================================
Testing DFS-LOOP-Mo (loop-avoiding with budget)
========================================
[dfs-loop-Mo] from Malmö to Göteborg: shortest 153 minutes (10.64 us)
[dfs-loop-Mo] from Göteborg to Stockholm: shortest 211 minutes (161.65 us)
[dfs-loop-Mo] from Malmö to Stockholm: shortest 273 minutes (2031.46 us)
[dfs-loop-Mo] from Stockholm to Sundsvall: shortest 327 minutes (248.90 us)
[dfs-loop-Mo] from Stockholm to Umeå: shortest 517 minutes (45731.77 us)
[dfs-loop-Mo] from Göteborg to Sundsvall: shortest 515 minutes (23048.61 us)
[dfs-loop-Mo] from Sundsvall to Umeå: shortest 190 minutes (1.08 us)
[dfs-loop-Mo] from Umeå to Göteborg: shortest 705 minutes (6698.79 us)
[dfs-loop-Mo] from Göteborg to Umeå: shortest 705 minutes (59363.15 us)

========================================
Testing DFS-BB (branch-and-bound)
========================================
[dfs-bb] from Malmö to Göteborg: shortest 153 minutes (14.57 us)
[dfs-bb] from Göteborg to Stockholm: shortest 211 minutes (32.25 us)
[dfs-bb] from Malmö to Stockholm: shortest 273 minutes (48.47 us)
[dfs-bb] from Stockholm to Sundsvall: shortest 327 minutes (104.63 us)
[dfs-bb] from Stockholm to Umeå: shortest 517 minutes (938.56 us)
[dfs-bb] from Göteborg to Sundsvall: shortest 515 minutes (994.56 us)
[dfs-bb] from Sundsvall to Umeå: shortest 190 minutes (15.48 us)
[dfs-bb] from Umeå to Göteborg: shortest 705 minutes (115.96 us)
[dfs-bb] from Göteborg to Umeå: shortest 705 minutes (5067.98 us)

========================================
Testing Dijkstra
========================================
[dijkstra] shortest 153 minutes (3.03 us)
cities visited: 14
[dijkstra] shortest 211 minutes (5.11 us)
cities visited: 32
[dijkstra] shortest 273 minutes (5.74 us)
cities visited: 30
[dijkstra] shortest 327 minutes (8.73 us)
cities visited: 44
[dijkstra] shortest 517 minutes (6.15 us)
cities visited: 48
[dijkstra] shortest 515 minutes (9.08 us)
cities visited: 46
[dijkstra] shortest 190 minutes (3.20 us)
cities visited: 4
[dijkstra] shortest 705 minutes (4.93 us)
cities visited: 36
[dijkstra] shortest 705 minutes (8.09 us)
cities visited: 48

3rd, only dijkstra:
./test_dijkstra.sh
========================================
Dijkstra Benchmark - European Cities
========================================

From Paris to 12 European cities:
========================================
[dijkstra] shortest 478 minutes (6.70 us)
cities visited: 34
[dijkstra] shortest 144 minutes (2.98 us)
cities visited: 7
[dijkstra] shortest 572 minutes (5.20 us)
cities visited: 41
unknown city: Rome (0.68 us)
[dijkstra] shortest 236 minutes (3.46 us)
cities visited: 16
unknown city: Brussels (1.38 us)
unknown city: Vienna (0.43 us)
unknown city: Prague (0.72 us)
unknown city: Copenhagen (0.92 us)
[dijkstra] shortest 1048 minutes (9.38 us)
cities visited: 96
unknown city: Warsaw (0.76 us)
[dijkstra] shortest 847 minutes (9.69 us)
cities visited: 66

---

## 6. Benchmarks - European Cities

As per assignment requirements, computing shortest paths from one European city to others:

**Source City:** Paris

| Destination | Distance (min) | Time (us) | Cities Visited (done[] entries) | Notes |
|-------------|----------------|-----------|----------------------------------|-------|
| Berlin      | 478            | 6.70      | 34                               | ✓     |
| London      | 144            | 2.98      | 7                                | ✓     |
| Madrid      | 572            | 5.20      | 41                               | ✓     |
| Rome        | -              | 0.68      | -                                | Not in dataset (lookup only) |
| Amsterdam   | 236            | 3.46      | 16                               | ✓     |
| Brussels    | -              | 1.38      | -                                | Not in dataset (lookup only) |
| Vienna      | -              | 0.43      | -                                | Not in dataset (lookup only) |
| Prague      | -              | 0.72      | -                                | Not in dataset (lookup only) |
| Copenhagen  | -              | 0.92      | -                                | Not in dataset (lookup only) |
| Stockholm   | 1048           | 9.38      | 96                               | ✓     |
| Warsaw      | -              | 0.76      | -                                | Not in dataset (lookup only) |
| Budapest    | 847            | 9.69      | 66                               | ✓     |

**Observations:**
- Successful routes: 2.98-9.69 us for 7-96 cities explored
- Hash table lookups for missing cities: 0.43-1.38 us (extremely fast O(1) average)
- Execution time scales with cities visited (Stockholm: 96 cities, 9.38 us)
- Short distances are fast (London: 7 cities, 2.98 us)
- Even failed lookups demonstrate hash table efficiency (<2 us)
- Time correlates with done[] entries, confirming O((V + E) log V) complexity

---

## 7. Complexity Analysis

**Given:**
- n cities
- Computing shortest paths from one source

**Algorithm steps:**
1. Remove path from priority queue: O(log V)
2. Check if first visit to city: O(1)
3. Expand neighbors: O(degree) edges
4. Each neighbor insertion: O(log V)

**Total complexity:**
- Each city expanded once: n iterations
- Each edge processed once: E total edges
- Priority queue operations: O(log V) per operation
- **Result: O((V + E) log V)**

**Benchmark validation (Swedish dataset: 52 cities, 75 edges):**

| Route | Dijkstra (us) | DFS-BB (us) | Speedup | Cities Visited |
|-------|---------------|-------------|---------|----------------|
| Malmö → Göteborg | 3.03 | 14.57 | 4.8x | 14 |
| Göteborg → Stockholm | 5.11 | 32.25 | 6.3x | 32 |
| Malmö → Stockholm | 5.74 | 48.47 | 8.4x | 30 |
| Stockholm → Sundsvall | 8.73 | 104.63 | 12.0x | 44 |
| Stockholm → Umeå | 6.15 | 938.56 | 152.6x | 48 |
| Göteborg → Sundsvall | 9.08 | 994.56 | 109.5x | 46 |
| Göteborg → Umeå | 8.09 | 5067.98 | 626.5x | 48 |

**Key findings:**
- Dijkstra consistently 5-600x faster than best DFS variant (DFS-BB)
- Speedup increases dramatically for longer paths (626x for Göteborg → Umeå)
- Cities visited: 4-48 (only explores necessary nodes)
- European dataset: 2.98-9.69 us for 7-96 cities
- Hash table lookups: <2 us even for missing cities

**Comparison with DFS:**
- DFS explores paths (exponential branches, repeated work)
- Dijkstra explores frontiers (each city visited once)
- done[] array prevents redundant exploration
- Priority queue ensures optimal expansion order
- Result: Dijkstra scales to large graphs where DFS becomes impractical