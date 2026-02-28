/**
 * zip2.c - Postal code lookup using integer-based zip codes
 * Converts string zip codes to integers for faster comparison
 * Implements linear and binary search, plus collision analysis
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>

#define AREAS 100000   // Maximum number of postal code areas
#define BUFFER 200     // Buffer size for reading lines

// Represents a postal code area with integer zip code
typedef struct area {
    char *name;  // Area name
    int zip;     // Zip code as integer (e.g., "111 15" -> 11115)
    int pop;     // Population
} area;

// Collection of postal code areas
typedef struct codes {
    area *areas;  // Array of areas
    int n;        // Number of areas
} codes;

/**
 * Read postal codes from CSV file and convert zip to integer
 * Zip format "XXX YY" is converted to integer XXXYYY
 * Returns NULL on failure
 */
codes *read_postcodes(char *file) {
    codes *postnr = (codes*) malloc(sizeof(codes));  // Allocate codes structure
    area *areas = (area*) malloc(sizeof(area)*AREAS);  // Allocate array for all areas
    FILE *fptr = fopen(file, "r");  // Open CSV file
    if (fptr == NULL) {  // Check if file opened successfully
        free(areas);
        free(postnr);
        return NULL;
    }
    int k = 0;  // Counter for number of areas read
    char *lineptr = malloc(sizeof(char)*BUFFER);  // Buffer for reading lines
    size_t n = BUFFER;
    while((k < AREAS) && (getline(&lineptr, &n, fptr) > 0)) {  // Read each line
        char *copy = (char*) malloc(sizeof(char)*n);  // Copy line for tokenization
        strcpy(copy, lineptr);
        area a;
        char *zip = strtok(copy, ",");  // Parse zip code string
		a.zip = atoi(zip)*100 + atoi(zip+3);  // Convert "111 15" to 11115
        a.name = strtok(NULL, ",");  // Parse area name
        a.pop = atoi(strtok(NULL, ","));  // Parse population
        areas[k++] = a;  // Store area in array
        free(copy);  // Free copy since name is copied by value
    }
    free(lineptr);  // Free line buffer
    fclose(fptr);  // Close file
    postnr->areas = areas;
    postnr->n = k;  // Store count of areas
    return postnr;
}

// Print all postal codes
void codes_print(codes *postnr){
	area *areas = postnr->areas;
	int length = postnr->n;
	for (int i = 0; i < length; i++){
		area a = areas[i];
		printf("name=%s\t zip=%d\t pop=%d\n", a.name, a.zip, a.pop);
	}
}

/**
 * Linear search for postal code by integer zip
 * Time complexity: O(n)
 */
area* codes_linear_search(codes *postnr, int zip){
	int i = 0;
	int length = postnr->n;
	area *areas = postnr->areas;
	while (i < length && zip != areas[i].zip){  // Compare each zip sequentially
		i++;
	}
	if (i == postnr->n){  // Reached end without finding
		return NULL;
	}
	return &postnr->areas[i];  // Return pointer to found area
}


/**
 * Binary search for postal code by integer zip
 * Time complexity: O(log n)
 */
area* codes_binary_search(codes *postnr, int zip){
	int lo = 0;  // Lower bound
	int hi = postnr->n-1;  // Upper bound
	area *areas = postnr->areas;
	while (lo <= hi){  // Continue while search space exists
		int mid = (lo + hi) / 2;  // Fixed: correct midpoint calculation
		int cmp = zip - areas[mid].zip;  // Compare with middle element
		if (cmp < 0){  // Target is in left half
			hi = mid - 1; // turn left
		}
		else if (cmp > 0){  // Target is in right half
			lo = mid + 1; // turn right
		}
		else{  // Found exact match
			return &areas[mid];
		}
	}
	return NULL;  // Not found
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

/**
 * Analyze hash collision distribution
 * Shows how zip codes would distribute across hash table buckets
 */
void collisions(codes *postnr, int mod) {
    int mx = 20;  // Maximum collision count to track
    int data[mod];  // Count of entries per bucket
    int cols[mx];  // Histogram of collision counts
    for (int i = 0; i < mod; i++) data[i] = 0;  // Initialize bucket counts
    for (int i = 0; i < mx; i++) cols[i] = 0;  // Initialize histogram
    for (int i = 0; i < postnr->n; i++) {  // Count entries per bucket
        if (postnr->areas[i].name != NULL) {  // only count actual entries
            int index = (postnr->areas[i].zip)%mod;  // Hash function
            data[index]++;
        }
    }
    int sum = 0;
    for(int i = 0; i < mod; i++) {  // Build histogram
        sum += data[i];
        if (data[i] < mx)
            cols[data[i]]++;  // Count buckets with this many entries
    }
    printf("%d (%d) : \n", mod, sum);
    printf("Collision distribution:\n");
    for (int i = 0; i < mx; i++) {  // Print histogram
        printf("%d: %d\n", i, cols[i]);
    }
    printf("\nBucket contents:\n");
    for (int i = 0; i < mod; i++) {  // Print non-empty buckets
        if (data[i] > 0)
            printf("bucket %d: %d entries\n", i, data[i]);
    }
    printf("\nAreas in each bucket:\n");
    for (int bucket = 0; bucket < mod; bucket++) {  // Print all areas by bucket
        for (int i = 0; i < postnr->n; i++) {
            if (postnr->areas[i].name != NULL && (postnr->areas[i].zip) % mod == bucket) {
                printf("bucket %d: %s (zip=%d)\n", bucket, postnr->areas[i].name, postnr->areas[i].zip);
            }
        }
    }
    printf("\n");
}

// Calculate elapsed time in nanoseconds
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec- t_start->tv_nsec) + (t_stop->tv_sec- t_start->tv_sec)*1000000000;
}

// Benchmark a search function with given zip code
double benchmark_search(area* (*search_func)(codes*, int), codes *postnr, int zip, int repeat) {
	double min = DBL_MAX;
	struct timespec start, stop;
	for (int j = 0; j < 1024; j++) {
		clock_gettime(CLOCK_MONOTONIC, &start);
		for (int i = 0; i < repeat; i++) {
			volatile area *a = search_func(postnr, zip);
		}
		clock_gettime(CLOCK_MONOTONIC, &stop);
		
		double current_execution = (double) nano_seconds(&start, &stop) / (double) repeat;
		if (current_execution < min) min = current_execution;
	}
	return min;
}

// Benchmark binary search performance
void benchmark(){
	codes *postnr = read_postcodes("zipcodes.csv");
	if (postnr == NULL) {
		printf("Failed to read postcodes\n");
		return;
	}
	int repeat = 1024;

	printf("(Int array) Linear search 11115: %f nanoseconds\n", 
	       benchmark_search(codes_linear_search, postnr, 11115, repeat));
	printf("(Int array) Linear search 98499: %f nanoseconds\n", 
	       benchmark_search(codes_linear_search, postnr, 98499, repeat));
	printf("(Int array) Binary search 11115: %f nanoseconds\n", 
	       benchmark_search(codes_binary_search, postnr, 11115, repeat));
	printf("(Int array) Binary search 98499: %f nanoseconds\n", 
	       benchmark_search(codes_binary_search, postnr, 98499, repeat));
}

int main(){
    /*
	codes *postnr = read_postcodes("zipcodes.csv");

	area *a = codes_binary_search(postnr, 75320);
	area_print(a);
	
	a = codes_binary_search(postnr, 58220);
	area_print(a);

	a = codes_binary_search(postnr, 21420);
	area_print(a);
	
	a = codes_binary_search(postnr, 0);
	area_print(a);
    */
	// collisions(postnr, 17);
    benchmark();
	// codes_print(postnr);
}