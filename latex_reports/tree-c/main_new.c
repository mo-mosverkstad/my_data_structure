#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "benchmark.h"
#include "bfs_sequence.h"

int main(int argc, char *argv[]) {
    /*
    srand(123456u);
    
    if (argc > 1 && strcmp(argv[1], "--latex") == 0) {
        const char *output = argc > 2 ? argv[2] : "benchmark_output.tex";
        run_benchmark_latex(output);
    } else {
        run_benchmark();
    }
    */
    
    tree *myTree = construct_tree();

    printf("No nodes: ");
    breadth_first_print(myTree);

    
    add(myTree, 5);
    printf("1 node: ");
    breadth_first_print(myTree);

    add(myTree, 2);
    add(myTree, 7);
    add(myTree, 1);
    add(myTree, 3);
    printf("5 nodes: ");
    breadth_first_print(myTree);

    add(myTree, 6);
    add(myTree, 9);
    
    printf("Fully filled: ");
    breadth_first_print(myTree);

    sequence *seq = create_sequence(myTree);

    printf("%d ", next(seq));
    printf("%d ", next(seq));
    printf("%d ", next(seq));

    printf("\nPause for a brief \n");

    add(myTree, -2);
    add(myTree, 4);
    add(myTree, 12);

    for (unsigned int i = 0; i < 10; i++) printf("%d ", next(seq));

    printf("\n");
    breadth_first_print(myTree);

    free_sequence(seq);
    free_tree(myTree);
    
    return 0;
}
