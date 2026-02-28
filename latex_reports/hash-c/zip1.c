/**
 * zip1.c - Postal code lookup using string-based zip codes
 * Implements linear and binary search on sorted array of postal codes
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define AREAS 100000   // Maximum number of postal code areas
#define BUFFER 200     // Buffer size for reading lines

// Represents a postal code area with name, zip code string, and population
typedef struct area {
    char *name;  // Area name
    char *zip;   // Zip code as string (e.g., "111 15")
    int pop;     // Population
} area;

// Collection of postal code areas
typedef struct codes {
    area *areas;  // Array of areas
    int n;        // Number of areas
} codes;

/**
 * Read postal codes from CSV file
 * Returns NULL on failure, codes structure on success
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
        a.zip = strtok(copy, ",");  // Parse zip code
        a.name = strtok(NULL, ",");  // Parse area name
        a.pop = atoi(strtok(NULL, ","));  // Parse population
        areas[k++] = a;  // Store area in array
    }
    free(lineptr);  // Free line buffer
    fclose(fptr);  // Close file
    postnr->areas = areas;
    postnr->n = k;  // Store count of areas
    return postnr;
}

// Print all postal codes in the collection
void codes_print(codes *postnr){
	area *areas = postnr->areas;
	int length = postnr->n;
	for (int i = 0; i < length; i++){
		area a = areas[i];
		printf("name=%s\t zip=%s\t pop=%d\n", a.name, a.zip, a.pop);
	}
}

/**
 * Linear search for postal code
 * Time complexity: O(n)
 */
area* codes_linear_search(codes *postnr, char *zip){
	int i = 0;
	int length = postnr->n;
	area *areas = postnr->areas;
	while (i < length && strcmp(zip, areas[i].zip) != 0){  // Compare each zip sequentially
		i++;
	}
	if (i == postnr->n){  // Reached end without finding
		return NULL;
	}
	return &postnr->areas[i];  // Return pointer to found area
}


/**
 * Binary search for postal code (requires sorted array)
 * Time complexity: O(log n)
 */
area* codes_binary_search(codes *postnr, char *zip){
	int lo = 0;  // Lower bound
	int hi = postnr->n-1;  // Upper bound
	area *areas = postnr->areas;
	while (lo <= hi){  // Continue while search space exists
		int mid = (lo + hi) / 2;  // Fixed: correct midpoint calculation
		int cmp = strcmp(zip, areas[mid].zip);  // Compare with middle element
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


// Print a single area's information
void area_print(area *a){
	if (a == NULL){
		printf("NULL\n");
	}
	else{
		printf("name=%s\t zip=%s\t pop=%d\n", a->name, a->zip, a->pop);
	}
}

// TODO: benchmark searches for ”111 15” and ”984 99”

// Calculate elapsed time in nanoseconds
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec- t_start->tv_nsec) + (t_stop->tv_sec- t_start->tv_sec)*1000000000;
}

// Benchmark a search function with given zip code
double benchmark_search(area* (*search_func)(codes*, char*), codes *postnr, char *zip, int repeat) {
	double execution = 0;
	struct timespec start, stop;
	for (int j = 0; j < 1024; j++) {
		clock_gettime(CLOCK_MONOTONIC, &start);
		for (int i = 0; i < repeat; i++) {
			volatile area *a = search_func(postnr, zip);
		}
		clock_gettime(CLOCK_MONOTONIC, &stop);
		
		double current_execution = (double) nano_seconds(&start, &stop) / (double) repeat;
		if (execution == 0 || current_execution < execution) {
			execution = current_execution;
		}
	}
	return execution;
}

// Benchmark binary search performance
void benchmark(){
	codes *postnr = read_postcodes("zipcodes.csv");
	if (postnr == NULL) {
		printf("Failed to read postcodes\n");
		return;
	}
	int repeat = 1024;

	printf("(Char array) Linear search 111 15: %f nanoseconds\n", 
	       benchmark_search(codes_linear_search, postnr, "111 15", repeat));
	printf("(Char array) Linear search 984 99: %f nanoseconds\n", 
	       benchmark_search(codes_linear_search, postnr, "984 99", repeat));
	printf("(Char array) Binary search 111 15: %f nanoseconds\n", 
	       benchmark_search(codes_binary_search, postnr, "111 15", repeat));
	printf("(Char array) Binary search 984 99: %f nanoseconds\n", 
	       benchmark_search(codes_binary_search, postnr, "984 99", repeat));
}

int main(){
	/*
	codes *postnr = read_postcodes("zipcodes.csv");
	area *a = codes_binary_search(postnr, "753 20");
	area_print(a);
	
	a = codes_binary_search(postnr, "582 20");
	area_print(a);

	a = codes_binary_search(postnr, "214 20");
	area_print(a);
	
	a = codes_binary_search(postnr, "no");
	area_print(a);
	*/

	benchmark();
	
	// codes_print(postnr);
}