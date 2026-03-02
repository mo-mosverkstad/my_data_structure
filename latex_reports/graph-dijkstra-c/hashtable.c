#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashtable.h"

/*
struct entry {
    void *key;
    void *value;
    struct entry *next;
};

struct hashtable {
    struct entry **buckets;
    size_t cap;
    size_t size;
    size_t (*hash)(const void *key, const void *mod);
    int (*cmp)(const void *a, const void *b);
};
*/

struct hashtable *ht_create(size_t cap, size_t (*hash)(const void *, size_t), int (*cmp)(const void *, const void *)){
    struct hashtable *ht = malloc(sizeof(struct hashtable));
    if (!ht) return NULL;
    ht->buckets = calloc(cap, sizeof(struct entry *));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    ht->cap = cap;
    ht->size = 0;
    ht->hash = hash;
    ht->cmp = cmp;
    return ht;
}

void ht_free(struct hashtable *ht){
    if (!ht) return;
    for (size_t i = 0; i < ht->cap; i++) {
        struct entry *e = ht->buckets[i];
        while (e) {
            struct entry *next = e->next;
            free(e);
            e = next;
        }
    }
    free(ht->buckets);
    free(ht);
}

// true for successful operation, false for failed operation
bool ht_insert(struct hashtable *ht, void *key, void *value) {
    if (!ht) return false;
    size_t index = ht->hash(key, ht->cap);
    struct entry *e = ht->buckets[index];
    while (e) {
        if (ht->cmp(e->key, key) == 0) {
            e->value = value;
            return true;
        }
        e = e->next;
    }

    struct entry *new_entry = malloc(sizeof(struct entry));
    if (!new_entry) return false;
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = ht->buckets[index];
    ht->buckets[index] = new_entry;
    ht->size++;
    return true;
}

// valid pointer adress for successful operation, NULL for failed operation
void *ht_get(struct hashtable *ht, void *key) {
    if (!ht) return NULL;
    size_t index = ht->hash(key, ht->cap);
    struct entry *e = ht->buckets[index];
    while (e) {
        if (ht->cmp(e->key, key) == 0)
            return e->value;
        e = e->next;
    }
    return NULL;
}

bool ht_remove(struct hashtable *ht, void *key) {
    if (!ht) return false;
    size_t index = ht->hash(key, ht->cap);
    struct entry *e = ht->buckets[index];
    struct entry *prev = NULL;
    while (e) {
        if (ht->cmp(e->key, key) == 0) {
            if (prev)
                prev->next = e->next;
            else
                ht->buckets[index] = e->next;
            free(e);
            ht->size--;
            return true;
        }
        prev = e;
        e = e->next;
    }
    return false;
}

void ht_print(struct hashtable *ht) {
    if (!ht) return;
    printf("Hashtable{\n");
    for (size_t i = 0; i < ht->cap; i++) {
        struct entry *e = ht->buckets[i];
        if (e) {
            printf("  [%zu]:", i);
            while (e) {
                printf(" (%s -> %s)", (char *)e->key, (char *)e->value);
                e = e->next;
            }
            printf("\n");
        }
    }
    printf("}\n");
}

size_t hash_str(const void *name, size_t mod) {
    const unsigned char *s = name;
    size_t h = 0;
    int i = 0;
    unsigned char c = 0;

    while ((c = s[i]) != 0){
        h = (h*31 + c) % mod;
        i++;
    }

    return h;
}