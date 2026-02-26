#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AREAS 100000
#define BUFFER 200
#define MOD 9

typedef struct area {
    char *name;
    int zip;
    int pop;
    struct area *next;
} area;

typedef struct codes {
    area **areas;
    int n;
} codes;

int hash(int zip, int mod){
    return zip % mod;
}

// NULL returned if failure to open file or malloc data
codes *read_postcodes(char *file, unsigned int size, int mod) {
    codes *postnr = (codes*) malloc(sizeof(codes));
    if (postnr == NULL) return NULL;
    
    area **areas = (area**) calloc(size, sizeof(area *));
    if (areas == NULL) {
        free(postnr);
        return NULL;
    }
    
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL) {
        free(areas);
        free(postnr);
        return NULL;
    }
    
    char *lineptr = malloc(sizeof(char)*BUFFER);
    if (lineptr == NULL) {
        fclose(fptr);
        free(areas);
        free(postnr);
        return NULL;
    }
    
    size_t n = BUFFER;
    while(getline(&lineptr, &n, fptr) > 0) {
        char *copy = (char*) malloc(sizeof(char)*n);
        if (copy == NULL) continue;
        
        strcpy(copy, lineptr);
        area *a = (area*) malloc(sizeof(area));
        if (a == NULL) {
            free(copy);
            continue;
        }
        
        char *zip = strtok(copy, ",");
		int zipnum = atoi(zip)*100 + atoi(zip+3);
        int hashval = hash(zipnum, mod);
		a->zip = zipnum;
        a->name = strtok(NULL, ",");
        a->pop = atoi(strtok(NULL, ","));
        a->next = areas[hashval];
        areas[hashval] = a;
    }
    
    free(lineptr);
    fclose(fptr);
    postnr->areas = areas;
    postnr->n = size;
    return postnr;
}

void collisions(codes *postnr, int mod) {
    int mx = 20;
    int data[mod];
    int cols[mx];
    for (int i = 0; i < mod; i++) data[i] = 0;
    for (int i = 0; i < mx; i++) cols[i] = 0;
    for (int i = 0; i < mod; i++) {
        area *current = postnr->areas[i];
        while (current != NULL) {
            data[i]++;
            current = current->next;
        }
    }
    int sum = 0;
    for(int i = 0; i < mod; i++) {
        sum += data[i];
        if (data[i] < mx)
            cols[data[i]]++;
    }
    printf("%d (%d) : \n", mod, sum);
    printf("Collision distribution:\n");
    for (int i = 0; i < mx; i++) {
        printf("%d: %d\n", i, cols[i]);
    }
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
    printf("\n");
}

void codes_print(codes *postnr){
    for (int i = 0; i < postnr->n; i++){
        area *current = postnr->areas[i];
        while(current) {
            printf("bucket %d: name=%s, zip=%d, pop=%d\n", i, current->name, current->zip, current->pop);
            current = current->next;
        }
    }
}

area* codes_lookup(codes *postnr, int zip) {
    int index = hash(zip, postnr->n);   // find bucket
    area *current = postnr->areas[index];
    while (current) {
        if (current->zip == zip) return current;
        current = current->next;
    }
    return NULL; // not found
}


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

	area *a = codes_lookup(postnr, 75320);
	area_print(a);
	
	a = codes_lookup(postnr, 58220);
	area_print(a);

	a = codes_lookup(postnr, 21420);
	area_print(a);
	
	a = codes_lookup(postnr, 0);
	area_print(a);
	
	// collisions(postnr, MOD);
	codes_print(postnr);
}