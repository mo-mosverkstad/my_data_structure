#ifndef LATEX_OUTPUT_H
#define LATEX_OUTPUT_H

#include <stddef.h>

void format_number_latex(char *buf, size_t bufsize, long num);
char* read_template(const char *filename);
char* replace_placeholder(const char *template, const char *placeholder, const char *value);
void output_latex(const char *output_file, size_t *sizes, size_t nsizes, 
                  long *build_rec, long *build_iter, long *lookup_balanced, 
                  long *lookup_shuffled, long *lookup_unbalanced, long *lookup_arr);

#endif
