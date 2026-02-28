/**
 * zip2array.c - Direct array indexing for postal code lookup
 * Uses zip code as array index for O(1) lookup time
 * Trade-off: Uses more memory (100K array) for faster access
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER 200       // Buffer size for reading lines
#define MAX_ZIP 99999    // Maximum zip code value (array size)

// Represents a postal code area
typedef struct area {
    char *name;  // Area name (NULL if slot unused)
    int zip;     // Zip code as integer
    int pop;     // Population
} area;

// Collection using direct array indexing
typedef struct codes {
    area *areas;  // Array indexed by zip code
} codes;

/**
 * Read postal codes and store using zip as array index
 * Creates sparse array where areas[zipcode] contains that area's data
 * Returns NULL on failure
 */
codes *read_postcodes(char *file) {
    codes *postnr = (codes*) malloc(sizeof(codes));  // Allocate codes structure
    area *areas = (area*) calloc(MAX_ZIP + 1, sizeof(area));  // Allocate sparse array indexed by zip
    FILE *fptr = fopen(file, "r");  // Open CSV file
    if (fptr == NULL) {  // Check if file opened successfully
        free(areas);
        free(postnr);
        return NULL;
    }
    char *lineptr = malloc(sizeof(char)*BUFFER);  // Buffer for reading lines
    size_t n = BUFFER;
    while(getline(&lineptr, &n, fptr) > 0) {  // Read each line
        char *copy = (char*) malloc(sizeof(char)*n);  // Copy line for tokenization
        strcpy(copy, lineptr);
        char *zip = strtok(copy, ",");  // Parse zip code string
        int zipcode = atoi(zip)*100 + atoi(zip+3);  // Convert to integer
        areas[zipcode].zip = zipcode;  // Use zip as array index
        areas[zipcode].name = strtok(NULL, ",");  // Parse area name
        areas[zipcode].pop = atoi(strtok(NULL, ","));  // Parse population
    }
    fclose(fptr);  // Close file
    free(lineptr);  // Free line buffer
    postnr->areas = areas;
    return postnr;
}

/**
 * O(1) lookup by zip code - direct array access
 * Returns NULL if zip out of range or slot empty
 */
area* codes_lookup(codes *postnr, int zip) {
    if (zip < 0 || zip > MAX_ZIP || postnr->areas[zip].name == NULL)  // Validate zip and check if slot occupied
        return NULL;
    return &postnr->areas[zip];  // Direct array access - O(1)
}

// Print a single area
void area_print(area *a) {
    if (a == NULL) {
        printf("NULL\n");
    } else {
        printf("name=%s\t zip=%d\t pop=%d\n", a->name, a->zip, a->pop);
    }
}

// Calculate elapsed time in nanoseconds
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) + (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

// Benchmark O(1) lookup performance
void benchmark() {
    codes *postnr = read_postcodes("zipcodes.csv");
    if (postnr == NULL) {
        printf("Failed to read postcodes\n");
        return;
    }
    int repeat = 1024;  // Number of iterations per trial
    double execution = 0;  // Best execution time
    struct timespec start, stop;
    
    for (int j = 0; j < 1024; j++) {  // Run multiple trials
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < repeat; i++) {  // Repeat lookup many times
            volatile area *a = codes_lookup(postnr, 11115);  // volatile prevents optimization
        }
        clock_gettime(CLOCK_MONOTONIC, &stop);
        double current_execution = (double) nano_seconds(&start, &stop) / (double) repeat;  // Average per operation
        if (execution == 0 || current_execution < execution) {  // Keep minimum time
            execution = current_execution;
        }
    }
    printf("Execution time: %f nanoseconds\n", execution);
}

int main() {
    codes *postnr = read_postcodes("zipcodes.csv");
    if (postnr == NULL) {
        printf("Failed to read postcodes\n");
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
    
    benchmark();
}
