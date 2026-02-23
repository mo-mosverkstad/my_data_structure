#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "benchmark.h"

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

    add(myTree, 5);
    add(myTree, 3);
    add(myTree, 7);
    add(myTree, 4);
    add(myTree, 6);

    print_tree(myTree);

    printf("Lookup 4: %d\n", recursive_lookup(myTree, 4));
    printf("Lookup 10: %d\n", recursive_lookup(myTree, 10));
    
    tree_print_inorder_stack(myTree);
    
    tree_delete(myTree, 7);
    
    tree_print_inorder_stack(myTree);

    free_tree(myTree);
    
    return 0;
}
