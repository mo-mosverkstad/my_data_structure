#!/bin/bash

CSV="europe.csv"

echo "========================================"
echo "Dijkstra Benchmark - European Cities"
echo "========================================"
echo ""
echo "From Paris to 12 European cities:"
echo "========================================"

./graph-dijkstra -f $CSV "Paris" "Berlin"
./graph-dijkstra -f $CSV "Paris" "London"
./graph-dijkstra -f $CSV "Paris" "Madrid"
./graph-dijkstra -f $CSV "Paris" "Rome"
./graph-dijkstra -f $CSV "Paris" "Amsterdam"
./graph-dijkstra -f $CSV "Paris" "Brussels"
./graph-dijkstra -f $CSV "Paris" "Vienna"
./graph-dijkstra -f $CSV "Paris" "Prague"
./graph-dijkstra -f $CSV "Paris" "Copenhagen"
./graph-dijkstra -f $CSV "Paris" "Stockholm"
./graph-dijkstra -f $CSV "Paris" "Warsaw"
./graph-dijkstra -f $CSV "Paris" "Budapest"
