#include "latex_output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void format_number_latex(char *buf, size_t bufsize __attribute__((unused)), long num) {
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "%ld", num);
    int len = strlen(tmp);
    int pos = 0;
    for (int i = 0; i < len; i++) {
        if (i > 0 && (len - i) % 3 == 0) {
            buf[pos++] = '\\';
            buf[pos++] = ',';
        }
        buf[pos++] = tmp[i];
    }
    buf[pos] = '\0';
}

char* read_template(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(size + 1);
    if (fread(buf, 1, size, f) != (size_t)size) {
        free(buf);
        fclose(f);
        return NULL;
    }
    buf[size] = '\0';
    fclose(f);
    return buf;
}

char* replace_placeholder(const char *template, const char *placeholder, const char *value) {
    const char *pos = strstr(template, placeholder);
    if (!pos) {
        char *dup = malloc(strlen(template) + 1);
        strcpy(dup, template);
        return dup;
    }
    size_t len = strlen(template) - strlen(placeholder) + strlen(value);
    char *result = malloc(len + 1);
    size_t prefix_len = pos - template;
    memcpy(result, template, prefix_len);
    strcpy(result + prefix_len, value);
    strcat(result, pos + strlen(placeholder));
    return result;
}

void output_latex(const char *output_file, size_t *sizes, size_t nsizes, 
                  long *build_rec, long *build_iter, long *lookup_balanced, 
                  long *lookup_shuffled, long *lookup_unbalanced, long *lookup_arr) {
    char *build_table_rows = malloc(4096);
    build_table_rows[0] = '\0';
    for (size_t s = 0; s < nsizes; ++s) {
        char rec_str[32], iter_str[32], line[256];
        format_number_latex(rec_str, sizeof(rec_str), build_rec[s]);
        format_number_latex(iter_str, sizeof(iter_str), build_iter[s]);
        snprintf(line, sizeof(line), "    %6zu   &  %14s  &  %14s  \\\\\n", sizes[s], rec_str, iter_str);
        strcat(build_table_rows, line);
    }

    char *build_rec_coords = malloc(2048), *build_iter_coords = malloc(2048);
    char *lookup_table_rows = malloc(8192);
    char *lookup_balanced_coords = malloc(2048), *lookup_shuffled_coords = malloc(2048);
    char *lookup_unbalanced_coords = malloc(2048), *lookup_arr_coords = malloc(2048);
    build_rec_coords[0] = build_iter_coords[0] = lookup_table_rows[0] = '\0';
    lookup_balanced_coords[0] = lookup_shuffled_coords[0] = '\0';
    lookup_unbalanced_coords[0] = lookup_arr_coords[0] = '\0';

    for (size_t s = 0; s < nsizes; ++s) {
        char line[256];
        snprintf(line, sizeof(line), "        (%zu, %ld)\n", sizes[s], build_rec[s]);
        strcat(build_rec_coords, line);
        snprintf(line, sizeof(line), "        (%zu, %ld)\n", sizes[s], build_iter[s]);
        strcat(build_iter_coords, line);
        
        char bal_str[32], shuf_str[32], unbal_str[32], arr_str[32];
        format_number_latex(bal_str, sizeof(bal_str), lookup_balanced[s]);
        format_number_latex(shuf_str, sizeof(shuf_str), lookup_shuffled[s]);
        format_number_latex(unbal_str, sizeof(unbal_str), lookup_unbalanced[s]);
        format_number_latex(arr_str, sizeof(arr_str), lookup_arr[s]);
        snprintf(line, sizeof(line), "    %6zu   &  %12s  &  %12s  &  %14s  &  %13s  \\\\\n", 
                 sizes[s], bal_str, shuf_str, unbal_str, arr_str);
        strcat(lookup_table_rows, line);
        
        snprintf(line, sizeof(line), "        (%zu, %ld)\n", sizes[s], lookup_balanced[s]);
        strcat(lookup_balanced_coords, line);
        snprintf(line, sizeof(line), "        (%zu, %ld)\n", sizes[s], lookup_shuffled[s]);
        strcat(lookup_shuffled_coords, line);
        snprintf(line, sizeof(line), "        (%zu, %ld)\n", sizes[s], lookup_unbalanced[s]);
        strcat(lookup_unbalanced_coords, line);
        snprintf(line, sizeof(line), "        (%zu, %ld)\n", sizes[s], lookup_arr[s]);
        strcat(lookup_arr_coords, line);
    }

    char *tmpl = read_template("templates/build_table.tex");
    if (tmpl) {
        char *out = replace_placeholder(tmpl, "{{BUILD_TABLE_ROWS}}", build_table_rows);
        FILE *fp = fopen(output_file, "w");
        if (fp) { fprintf(fp, "%s\n\n", out); fclose(fp); }
        free(out); free(tmpl);
    }

    tmpl = read_template("templates/build_figure.tex");
    if (tmpl) {
        char *out = replace_placeholder(tmpl, "{{BUILD_REC_COORDS}}", build_rec_coords);
        char *out2 = replace_placeholder(out, "{{BUILD_ITER_COORDS}}", build_iter_coords);
        FILE *fp = fopen(output_file, "a");
        if (fp) { fprintf(fp, "%s\n\n", out2); fclose(fp); }
        free(out2); free(out); free(tmpl);
    }

    tmpl = read_template("templates/lookup_table.tex");
    if (tmpl) {
        char *out = replace_placeholder(tmpl, "{{LOOKUP_TABLE_ROWS}}", lookup_table_rows);
        FILE *fp = fopen(output_file, "a");
        if (fp) { fprintf(fp, "%s\n\n", out); fclose(fp); }
        free(out); free(tmpl);
    }

    tmpl = read_template("templates/lookup_figure.tex");
    if (tmpl) {
        char *out = replace_placeholder(tmpl, "{{LOOKUP_BALANCED_COORDS}}", lookup_balanced_coords);
        char *out2 = replace_placeholder(out, "{{LOOKUP_SHUFFLED_COORDS}}", lookup_shuffled_coords);
        char *out3 = replace_placeholder(out2, "{{LOOKUP_UNBALANCED_COORDS}}", lookup_unbalanced_coords);
        char *out4 = replace_placeholder(out3, "{{LOOKUP_ARR_COORDS}}", lookup_arr_coords);
        FILE *fp = fopen(output_file, "a");
        if (fp) { fprintf(fp, "%s\n", out4); fclose(fp); }
        free(out4); free(out3); free(out2); free(out); free(tmpl);
    }

    free(build_table_rows); free(build_rec_coords); free(build_iter_coords);
    free(lookup_table_rows); free(lookup_balanced_coords); free(lookup_shuffled_coords);
    free(lookup_unbalanced_coords); free(lookup_arr_coords);
}
