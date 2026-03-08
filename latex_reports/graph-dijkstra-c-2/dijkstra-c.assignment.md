Here you go — a clean, plain‑text version of the PDF contents, formatted for easy reading.

***

# **Dijkstra to our rescue — in C**

**Algorithms and Data Structures, ID1021**  
**Johan Montelius**  
**Spring 2026**

***

## **Introduction**

This assignment continues the graph assignment where you searched for the quickest train ride in Sweden. In this assignment, you will improve the implementation by using **Dijkstra’s algorithm**.

The problem with the previous solution was that it didn't remember where it had been, causing repeated work. Dijkstra’s algorithm solves this by keeping track of the shortest path to nodes already visited. It can compute not only the shortest path from A to B, but from A to *all* other stations in the network.

The idea:  
We maintain the shortest known paths to cities we've reached. At each step, we expand the shortest path found so far. When the shortest path in the queue ends at the destination, we are done — all other known paths are longer.

Before implementing the algorithm, we need some supporting data structures.

***

## **Some Data Structures**

### **A city**

A city holds its name and a data structure containing its neighbours (dynamic array or linked list).

```c
typedef struct city {
    char *name;
    int id;
    ... neighbours;
} city;
```

When building the map, number the cities (0 to n). The integer ID will be used as an array index later.

***

### **A path**

A path consists of:

*   a city
*   the previous city on the path
*   the total distance in minutes from the origin

```c
typedef struct path {
    city *city;
    city *prev;
    int dist;
} path;
```

Each *path entry* represents a possible route to the destination. It only stores the previous city, so a full path must be reconstructed by walking backward.

***

### **done\[]**

As the algorithm runs, we store the shortest known path to each city in an array called **done**, indexed by city ID.

Example:  
When we find the shortest path from Malmö to Stockholm, `done[Stockholm]` will contain:

*   the distance
*   the previous city (Södertälje)

By following these links backward, we reconstruct the entire route.

We begin by putting the source city into the queue.

***

### **A priority queue**

We always expand the *shortest* known path.  
Thus, we use a **priority queue** of paths. You already have such a structure — adapt it to store and compare `path` entries.

***

## **Dijkstra’s Algorithm**

We explore the graph gradually, always choosing the city closest to the origin.

Process:

1.  Remove the shortest path from the queue.
2.  If the path ends at the destination → **we’re done**.
3.  If this is the first time we encounter the city:
    *   Place the path in the `done` array.
    *   Expand from this city:  
        For each neighbour, create a new path and insert it into the queue.

Initialization example:  
Shortest path from Malmö to Stockholm:  
First queue entry = `{ Malmö, 0, NULL }`.

Then we add Malmö to `done` and enqueue all neighbours of Malmö.

***

### **White Paper**

Before implementing the algorithm:

**Draw a picture** showing:

*   what’s in the `done[]` array
*   what’s in the priority queue
*   what happens each iteration

If you cannot visualize this, you will likely struggle with the implementation.

***

## **Benchmarks**

When everything works, you should find the path from Malmö to Kiruna *much faster* than with your previous solution. Benchmark your improvements.

Next, choose a European city and compute shortest paths to 12 other European cities. For each:

*   time taken
*   number of entries in `done[]`

The number of entries in `done[]` indicates how many cities were involved in the search.

***

## **Complexity Reasoning**

Assume:

*   `n` cities
*   We compute shortest paths from one source to all others

In each iteration:

*   We remove a path from the queue
*   If it’s the first time we see this city, we expand it and add its neighbours
*   Each city is expanded **once** → yields a factor of **n**

But there’s more:

*   How many neighbours per city?
*   How many paths are in the queue?
*   What is the cost of priority queue operations?

Estimate these and derive the total runtime complexity. Compare with benchmark results and see if they match your expectations.

***

If you'd like, I can also convert this into Markdown, a Word document, or a cleaned‑up text file.
