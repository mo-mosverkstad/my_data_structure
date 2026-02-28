/**
 * zip3.c - Hash table with separate chaining (linked lists)
 * Uses hash function with collision resolution via linked lists
 * Each bucket contains a linked list of areas that hash to same index
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AREAS 100000   // Maximum number of areas
#define BUFFER 200     // Buffer size for reading lines
#define MOD 14000      // Hash table size (number of buckets)

// Represents a postal code area in linked list
typedef struct area {
    char *name;         // Area name
    int zip;            // Zip code as integer
    int pop;            // Population
    struct area *next;  // Next area in collision chain
} area;

// Hash table with separate chaining
typedef struct codes {
    area **areas;  // Array of pointers to linked lists
    int n;         // Number of buckets
} codes;

/**
 * Hash function: simple modulo operation
 * Returns bucket index for given zip code
 */
int hash(int zip, int mod){
    return zip % mod;
}

/**
 * Read postal codes and build hash table with separate chaining
 * Collisions are resolved by prepending to linked list at bucket
 * Returns NULL on failure
 */
codes *read_postcodes(char *file, unsigned int size, int mod) {
    codes *postnr = (codes*) malloc(sizeof(codes));  // Allocate codes structure
    if (postnr == NULL) return NULL;
    
    area **areas = (area**) calloc(size, sizeof(area *));  // Allocate array of bucket pointers
    if (areas == NULL) {
        free(postnr);
        return NULL;
    }
    
    FILE *fptr = fopen(file, "r");  // Open CSV file
    if (fptr == NULL) {  // Check if file opened successfully
        free(areas);
        free(postnr);
        return NULL;
    }
    
    char *lineptr = malloc(sizeof(char)*BUFFER);  // Buffer for reading lines
    if (lineptr == NULL) {
        fclose(fptr);
        free(areas);
        free(postnr);
        return NULL;
    }
    
    size_t n = BUFFER;
    while(getline(&lineptr, &n, fptr) > 0) {  // Read each line
        char *copy = (char*) malloc(sizeof(char)*n);  // Copy line for tokenization
        if (copy == NULL) continue;
        
        strcpy(copy, lineptr);
        area *a = (area*) malloc(sizeof(area));  // Allocate new area node
        if (a == NULL) {
            free(copy);
            continue;
        }
        
        char *zip = strtok(copy, ",");  // Parse zip code string
		int zipnum = atoi(zip)*100 + atoi(zip+3);  // Convert to integer
        int hashval = hash(zipnum, mod);  // Calculate bucket index
		a->zip = zipnum;
        a->name = strtok(NULL, ",");  // Parse area name
        a->pop = atoi(strtok(NULL, ","));  // Parse population
        a->next = areas[hashval];  // Prepend to linked list
        areas[hashval] = a;  // Update bucket head
    }
    
    free(lineptr);  // Free line buffer
    fclose(fptr);  // Close file
    postnr->areas = areas;
    postnr->n = size;  // Store bucket count
    return postnr;
}

/**
 * Analyze collision distribution in hash table
 * Shows how many buckets have 0, 1, 2, ... entries
 * Fixed: Uses dynamic allocation to avoid stack overflow
 */
void collisions(codes *postnr, int mod) {
    int mx = 20;  // Maximum collision count to track
    int *data = (int*) calloc(mod, sizeof(int));  // Count of entries per bucket
    int *cols = (int*) calloc(mx, sizeof(int));  // Histogram of collision counts
    if (data == NULL || cols == NULL) {  // Check allocation success
        free(data);
        free(cols);
        return;
    }
    
    // Count entries in each bucket
    for (int i = 0; i < mod; i++) {
        area *current = postnr->areas[i];  // Get bucket head
        while (current != NULL) {  // Traverse linked list
            data[i]++;  // Count entry
            current = current->next;  // Move to next node
        }
    }
    int sum = 0;
    // Build collision distribution histogram
    for(int i = 0; i < mod; i++) {
        sum += data[i];  // Total entries
        if (data[i] < mx)
            cols[data[i]]++;  // Count buckets with this many entries
    }
    printf("%d (%d) : \n", mod, sum);
    printf("Collision distribution:\n");
    for (int i = 0; i < mx; i++) {  // Print histogram
        printf("%d: %d\n", i, cols[i]);
    }
    
    free(data);  // Free allocated memory
    free(cols);
    
    /*
    printf("\nBucket contents:\n");
    for (int i = 0; i < mod; i++) {
        if (data[i] > 0)
            printf("bucket %d: %d entries\n", i, data[i]);
    }
    
    printf("\nAreas in each bucket:\n");
    for (int bucket = 0; bucket < mod; bucket++) {
        area *current = postnr->areas[bucket];
        while (current != NULL) {
            printf("bucket %d: %s (zip=%d)\n", bucket, current->name, current->zip);
            current = current->next;
        }
    }
    */
    printf("\n");
}

// Print all entries in hash table
void codes_print(codes *postnr){
    for (int i = 0; i < postnr->n; i++){
        area *current = postnr->areas[i];
        while(current) {
            printf("bucket %d: name=%s, zip=%d, pop=%d\n", i, current->name, current->zip, current->pop);
            current = current->next;
        }
    }
}

/**
 * Lookup postal code in hash table
 * Time complexity: O(1) average, O(n) worst case
 */
area* codes_lookup(codes *postnr, int zip) {
    int index = hash(zip, postnr->n);  // Find bucket
    area *current = postnr->areas[index];  // Get bucket head
    // Search linked list at bucket
    while (current) {
        if (current->zip == zip) return current;  // Found match
        current = current->next;  // Move to next node
    }
    return NULL; // not found
}


// Print a single area
void area_print(area *a){
	if (a == NULL){
		printf("NULL\n");
	}
	else{
		printf("name=%s\t zip=%d\t pop=%d\n", a->name, a->zip, a->pop);
	}
}

int main(){
	codes *postnr = read_postcodes("zipcodes.csv", MOD, MOD);
    if (postnr == NULL) {
        printf("Error happened during file processing\n");
        return 1;
    }

    /*
	area *a = codes_lookup(postnr, 75320);
	area_print(a);
	
	a = codes_lookup(postnr, 58220);
	area_print(a);

	a = codes_lookup(postnr, 21420);
	area_print(a);
	
	a = codes_lookup(postnr, 0);
	area_print(a);
    */

	collisions(postnr, MOD);
	// codes_print(postnr);
}