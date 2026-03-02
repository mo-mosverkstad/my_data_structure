#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEF_CAP 16

struct vec {
    void *data;
    unsigned int len;
    unsigned int cap;
    size_t elem_size;
};

struct vec *vec_create(size_t elem_size);
void vec_free(struct vec *v);
bool vec_append(struct vec *v, const void *val);
void *vec_get(struct vec *v, unsigned int index);
void vec_print(struct vec *v, void (*print_val)(const void *));