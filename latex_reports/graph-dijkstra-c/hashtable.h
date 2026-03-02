#pragma once
#include <stdbool.h>

struct entry {
    void *key;
    void *value;
    struct entry *next;
};

struct hashtable {
    struct entry **buckets;
    size_t cap;
    size_t size;
    size_t (*hash)(const void *key, size_t mod);
    int (*cmp)(const void *a, const void *b);
};

struct hashtable *ht_create(size_t cap, size_t (*hash)(const void *, size_t), int (*cmp)(const void *, const void *));
void ht_free(struct hashtable *ht);

bool ht_insert(struct hashtable *ht, void *key, void *value);
void *ht_get(struct hashtable *ht, void *key);
bool ht_remove(struct hashtable *ht, void *key);
void ht_print(struct hashtable *ht);

size_t hash_str(const void *name, size_t mod);