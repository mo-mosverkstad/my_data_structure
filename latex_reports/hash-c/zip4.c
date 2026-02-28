/**
 * zip4.c - Hash table with open addressing (linear probing)
 * Uses linear probing for collision resolution with dynamic resizing
 * When table fills up, it doubles in size and rehashes all entries
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AREAS 100000   // Maximum number of areas
#define BUFFER 200     // Buffer size for reading lines
#define MOD 20000      // Initial hash table size

// Represents a postal code area (stored directly in array)
typedef struct area {
    char *name;  // Area name (NULL indicates empty slot)
    int zip;     // Zip code as integer
    int pop;     // Population
} area;

// Hash table with open addressing
typedef struct codes {
    area *areas;  // Array of areas (not pointers)
    int n;        // Current table size
} codes;

/**
 * Hash function: simple modulo operation
 * Returns initial probe position for given zip code
 */
int hash(int zip, int mod){
    return zip % mod;
}

/**
 * Read postal codes and build hash table with linear probing
 * Automatically resizes table when full (doubles size)
 * Returns NULL on failure
 */
codes *read_postcodes(char *file, unsigned int size) {
    codes *postnr = (codes*) malloc(sizeof(codes));  // Allocate codes structure
    if (postnr == NULL) return NULL;
    
    area *areas = (area*) calloc(size, sizeof(area));  // Allocate hash table array
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
        
        char *zip = strtok(copy, ",");  // Parse zip code string
		int zipnum = atoi(zip)*100 + atoi(zip+3);  // Convert to integer
        int hashval = hash(zipnum, size);  // Initial probe position
        int count = 0;

        // Linear probing: find next empty slot
        while (areas[hashval].name != (char *) 0 && count++ < size) {
            hashval = (hashval + 1) % size;  // Move to next slot
        }
        // Table full - resize and rehash
        if (count >= size){
            int new_size = size * 2;  // Double table size
            area *new_areas = (area *) calloc(new_size, sizeof(area));  // Allocate new table
            if (new_areas == NULL) {
                free(copy);
                continue;  // Skip entry if resize fails
            }
            // Rehash all existing entries into new table
            for (int i = 0; i < size; i++){
                if (areas[i].name != NULL) {  // Only rehash occupied slots
                    int newhash = hash(areas[i].zip, new_size);  // Recalculate hash
                    while (new_areas[newhash].name != NULL) {  // Linear probing
                        newhash = (newhash + 1) % new_size;  // Find empty slot
                    }
                    new_areas[newhash] = areas[i];  // Copy entry
                }
            }
            free(areas);  // Free old table
            areas = new_areas;  // Use new table
            size = new_size;  // Update size
            // Recalculate hash for current entry
            hashval = hash(zipnum, size);
            count = 0;
            while (areas[hashval].name != NULL && count++ < size) {
                hashval = (hashval + 1) % size;
            }
        }
        areas[hashval].zip = zipnum;  // Store zip code
        areas[hashval].name = strtok(NULL, ",");  // Fixed: correct delimiter
        areas[hashval].pop = atoi(strtok(NULL, ","));  // Store population
    }
    
    free(lineptr);  // Free line buffer
    fclose(fptr);  // Close file
    postnr->areas = areas;
    postnr->n = size;  // Store table size
    return postnr;
}

/**
 * Analyze probe distance distribution
 * Shows how far entries are from their ideal hash position
 * Fixed: Uses dynamic allocation to avoid stack overflow
 */
void collisions(codes *postnr) {
    int size = postnr->n;
    int mx = 1000;  // Maximum probe distance to track
    int *cols = (int*) calloc(mx, sizeof(int));  // Histogram of probe distances
    if (cols == NULL) {  // Check allocation success
        printf("Memory allocation failed\n");
        return;
    }
    
    int total = 0;
    for (int i = 0; i < size; i++) {  // Iterate through all slots
        if (postnr->areas[i].name != NULL) {  // Slot is occupied
            int ideal = hash(postnr->areas[i].zip, size);  // Ideal position
            int distance = ((i - ideal + size) % size);  // Probe distance
            if (distance < mx) cols[distance]++;  // Count this distance
            total++;  // Count total entries
        }
    }
    
    printf("Total entries: %d, Table size: %d\n", total, size);
    printf("Probe distance distribution:\n");
    for (int i = 0; i < mx; i++) {  // Print histogram
        if (cols[i] > 0)
            printf("%d probes: %d entries\n", i, cols[i]);
    }
    free(cols);  // Free allocated memory
    printf("\n");
}

// Print all entries in hash table
void codes_print(codes *postnr){
    for (int i = 0; i < postnr->n; i++){
        area current = postnr->areas[i];
        if (current.name == (char *) 0) continue;
        printf("slot %d: name=%s, zip=%d, pop=%d\n", i, current.name, current.zip, current.pop);
    }
}

/**
 * Lookup postal code using linear probing
 * Time complexity: O(1) average, O(n) worst case
 */
area* codes_lookup(codes *postnr, int zip) {
    int size = postnr->n;
    int index = hash(zip, size);  // Start at hash position
    int count = 0;
    // Linear probing until found or empty slot
    while (count++ < size) {
        area *current = &postnr->areas[index];  // Get current slot
        if (current->name == NULL) return NULL;  // Empty slot = not found
        if (current->zip == zip) return current;  // Found
        index = (index + 1) % size;  // Try next slot
    }
    return NULL;  // Not found after full table scan
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
	codes *postnr = read_postcodes("zipcodes.csv", MOD);
    if (postnr == NULL) {
        printf("Error happened during file processing\n");
        return 1;
    }

    
	area *a = codes_lookup(postnr, 75320);
	area_print(a);
	
	a = codes_lookup(postnr, 58220);
	area_print(a);

	a = codes_lookup(postnr, 21420);
	area_print(a);
	
	a = codes_lookup(postnr, 0);
	area_print(a);
    
	printf("size: %d\n", postnr->n);
	collisions(postnr);
	// codes_print(postnr);
}