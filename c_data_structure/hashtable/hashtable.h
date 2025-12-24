#define TABLE_SIZE 128

struct node {
    char* key;
    int value;
    struct node* next;
};

struct hashtable {
    struct node* buckets[TABLE_SIZE];
    unsigned int (*hash)(const char* key);
};

unsigned int hash1(const char* key);
unsigned int hash2(const char* key);
struct hashtable* hashtable_create(unsigned int (*hash)(const char* key));
void hashtable_destroy(struct hashtable* table);
void hashtable_insert(struct hashtable* table, const char* key, int value);
void hashtable_delete(struct hashtable* table, const char* key);
void hashtable_print(struct hashtable* table);
int hashtable_search(struct hashtable* table, const char* key);