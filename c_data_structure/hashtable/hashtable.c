#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

unsigned int hash1(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

unsigned int hash2(const char* key) {
    unsigned int value = 0;
    int i = 0;
    while(key[i] != 0) {
        value = ((31 * value) + key[i]) % TABLE_SIZE;
        i++;
    }
    return value;
}

struct hashtable* hashtable_create(unsigned int (*hash)(const char* key)) {
    struct hashtable* table = (struct hashtable*) malloc(sizeof(struct hashtable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    table->hash = hash;
    return table;
}

void hashtable_destroy(struct hashtable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct node* current = table->buckets[i];
        while (current) {
            struct node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table);
}

void hashtable_insert(struct hashtable* table, const char* key, int value) {
    unsigned int index = table->hash(key);
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->key = (char*) malloc(strlen(key) + 1);
    strcpy(new_node->key, key);
    new_node->value = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

void hashtable_delete(struct hashtable* table, const char* key) {
    unsigned int index = table->hash(key);
    struct node* current = table->buckets[index];
    struct node* previous = NULL;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (previous) {
                previous->next = current->next;
            } else {
                table->buckets[index] = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void hashtable_print(struct hashtable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct node* current = table->buckets[i];
        while (current) {
            printf("%s: %d\n", current->key, current->value);
            current = current->next;
        }
    }
}

int hashtable_search(struct hashtable* table, const char* key) {
    unsigned int index = table->hash(key);
    struct node* current = table->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}