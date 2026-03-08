#!/bin/bash

CSV="trains.csv"
TIMEOUT=10

run_with_timeout() {
    timeout $TIMEOUT "$@" || echo "[TIMEOUT] $*"
}

echo "========================================"
echo "Testing DFS-LIMIT (with budget)"
echo "========================================"
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit "Malmö" "Göteborg" 300
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit "Göteborg" "Stockholm" 500
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit "Malmö" "Stockholm" 700
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit "Stockholm" "Sundsvall" 500
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit "Stockholm" "Umeå" 1200
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit "Göteborg" "Sundsvall" 1000
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit "Sundsvall" "Umeå" 300
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit "Umeå" "Göteborg" 1200
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit "Göteborg" "Umeå" 1200

echo ""
echo "========================================"
echo "Testing DFS-LIMIT-Mo (with budget and visited flag)"
echo "========================================"
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit-Mo "Malmö" "Göteborg" 300
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit-Mo "Göteborg" "Stockholm" 500
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit-Mo "Malmö" "Stockholm" 700
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit-Mo "Stockholm" "Sundsvall" 500
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit-Mo "Stockholm" "Umeå" 1200
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit-Mo "Göteborg" "Sundsvall" 1000
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit-Mo "Sundsvall" "Umeå" 300
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit-Mo "Umeå" "Göteborg" 1200
run_with_timeout ./graph-dfs -f $CSV -a dfs-limit-Mo "Göteborg" "Umeå" 1200

echo ""
echo "========================================"
echo "Testing DFS-LOOP (loop-avoiding)"
echo "========================================"
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop "Malmö" "Göteborg"
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop "Göteborg" "Stockholm"
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop "Malmö" "Stockholm"
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop "Stockholm" "Sundsvall"
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop "Stockholm" "Umeå"
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop "Göteborg" "Sundsvall"
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop "Sundsvall" "Umeå"
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop "Umeå" "Göteborg"
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop "Göteborg" "Umeå"

echo ""
echo "========================================"
echo "Testing DFS-LOOP-Mo (loop-avoiding with budget)"
echo "========================================"
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop-Mo "Malmö" "Göteborg" 300
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop-Mo "Göteborg" "Stockholm" 500
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop-Mo "Malmö" "Stockholm" 700
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop-Mo "Stockholm" "Sundsvall" 500
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop-Mo "Stockholm" "Umeå" 1200
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop-Mo "Göteborg" "Sundsvall" 1000
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop-Mo "Sundsvall" "Umeå" 300
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop-Mo "Umeå" "Göteborg" 1200
run_with_timeout ./graph-dfs -f $CSV -a dfs-loop-Mo "Göteborg" "Umeå" 1200

echo ""
echo "========================================"
echo "Testing DFS-BB (branch-and-bound)"
echo "========================================"
run_with_timeout ./graph-dfs -f $CSV -a dfs-bb "Malmö" "Göteborg"
run_with_timeout ./graph-dfs -f $CSV -a dfs-bb "Göteborg" "Stockholm"
run_with_timeout ./graph-dfs -f $CSV -a dfs-bb "Malmö" "Stockholm"
run_with_timeout ./graph-dfs -f $CSV -a dfs-bb "Stockholm" "Sundsvall"
run_with_timeout ./graph-dfs -f $CSV -a dfs-bb "Stockholm" "Umeå"
run_with_timeout ./graph-dfs -f $CSV -a dfs-bb "Göteborg" "Sundsvall"
run_with_timeout ./graph-dfs -f $CSV -a dfs-bb "Sundsvall" "Umeå"
run_with_timeout ./graph-dfs -f $CSV -a dfs-bb "Umeå" "Göteborg"
run_with_timeout ./graph-dfs -f $CSV -a dfs-bb "Göteborg" "Umeå"

echo ""
echo "========================================"
echo "Testing Dijkstra"
echo "========================================"
run_with_timeout ./graph-dijkstra -f $CSV "Malmö" "Göteborg"
run_with_timeout ./graph-dijkstra -f $CSV "Göteborg" "Stockholm"
run_with_timeout ./graph-dijkstra -f $CSV "Malmö" "Stockholm"
run_with_timeout ./graph-dijkstra -f $CSV "Stockholm" "Sundsvall"
run_with_timeout ./graph-dijkstra -f $CSV "Stockholm" "Umeå"
run_with_timeout ./graph-dijkstra -f $CSV "Göteborg" "Sundsvall"
run_with_timeout ./graph-dijkstra -f $CSV "Sundsvall" "Umeå"
run_with_timeout ./graph-dijkstra -f $CSV "Umeå" "Göteborg"
run_with_timeout ./graph-dijkstra -f $CSV "Göteborg" "Umeå"
