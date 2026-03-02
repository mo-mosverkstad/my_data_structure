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

struct vec *vec_create(size_t elem_size) {
    if (elem_size == 0) return NULL;
    struct vec *v = malloc(sizeof(struct vec));
    if (!v) return NULL;
    v->data = malloc(DEF_CAP * elem_size);
    if (!v->data) {
        free(v);
        return NULL;
    }
    v->len = 0;
    v->cap = DEF_CAP;
    v->elem_size = elem_size;
    return v;
}

void vec_free(struct vec *v) {
    if (!v) return;
    free(v->data);
    free(v);
}

bool vec_append(struct vec *v, const void *val) {
    if (!v || !val) return false;
    if (v->len == v->cap) {
        unsigned int new_cap = v->cap * 2;
        void *new_data = realloc(v->data, new_cap * v->elem_size);
        if (!new_data) return false;
        v->data = new_data;
        v->cap = new_cap;
    }
    void *target = (void *) v->data + v->len * v->elem_size;
    memcpy(target, val, v->elem_size);
    v->len++;
    return true;
}

void *vec_get(struct vec *v, unsigned int index) {
    if (!v || index >= v->len) return NULL;
    return (void *)v->data + index * v->elem_size;
}

void vec_print(struct vec *v, void (*print_val)(const void *)) {
    if (!v || !print_val) return;
    printf("vec(%d)[", v->len);
    if (v->len > 0){
        print_val(v->data);
        for (unsigned int i = 1; i < v->len; i++) {
            void *val = (void *) v->data + i * v->elem_size;
            printf(", ");
            print_val(val);
        }
    }
    printf("]\n");
}