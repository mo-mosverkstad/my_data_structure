# Makefile for graph assignments (DFS and Dijkstra)
# Usage:
#   make            # builds both binaries
#   make clean

CC      := gcc
CFLAGS  := -O2 -std=c11 -Wall -Wextra
LDFLAGS := 

OBJS_COMMON := graph_base.o hashtable.o

all: graph-dfs graph-dijkstra

%.o: %.c graph.h
	$(CC) $(CFLAGS) -c $< -o $@

graph-dfs: graph-dfs.o $(OBJS_COMMON)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

graph-dijkstra: graph-dijkstra.o $(OBJS_COMMON)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o graph-dfs graph-dijkstra
