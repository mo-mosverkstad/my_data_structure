#include <stdlib.h>
#include <string.h>
#include "benchmark.h"

int main(int argc, char *argv[]) {
    srand(123456u);
    
    if (argc > 1 && strcmp(argv[1], "--latex") == 0) {
        const char *output = argc > 2 ? argv[2] : "benchmark_output.tex";
        run_benchmark_latex(output);
    } else {
        run_benchmark();
    }
    
    return 0;
}
