#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AREAS 100000
#define BUFFER 200
#define MOD 7

typedef struct area {
    char *name;
    int zip;
    int pop;
} area;

typedef struct codes {
    area *areas;
    int n;
} codes;

int hash(int zip, int mod){
    return zip % mod;
}

// NULL returned if failure to open file or malloc data
codes *read_postcodes(char *file, unsigned int size) {
    codes *postnr = (codes*) malloc(sizeof(codes));
    if (postnr == NULL) return NULL;
    
    area *areas = (area*) calloc(size, sizeof(area));
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
        
        char *zip = strtok(copy, ",");
		int zipnum = atoi(zip)*100 + atoi(zip+3);
        int hashval = hash(zipnum, size);
        int count = 0;

        while (areas[hashval].name != (char *) 0 && count++ < size) {
            hashval = (hashval + 1) % size;
        }
        if (count >= size){
            int new_size = size * 2;
            area *new_areas = (area *) calloc(new_size, sizeof(area));
            if (new_areas == NULL) {
                free(copy);
                continue;  // skip this entry if resize fails
            }
            for (int i = 0; i < size; i++){
                if (areas[i].name != NULL) {  // only rehash occupied slots
                    int newhash = hash(areas[i].zip, new_size);
                    while (new_areas[newhash].name != NULL) {  // linear probing in new table
                        newhash = (newhash + 1) % new_size;
                    }
                    new_areas[newhash] = areas[i];
                }
            }
            free(areas);
            areas = new_areas;
            size = new_size;
            // recalculate hash for current entry
            hashval = hash(zipnum, size);
            count = 0;
            while (areas[hashval].name != NULL && count++ < size) {
                hashval = (hashval + 1) % size;
            }
        }
        areas[hashval].zip = zipnum;
        areas[hashval].name = strtok(NULL, ", ");
        areas[hashval].pop = atoi(strtok(NULL, ", "));
    }
    
    free(lineptr);
    fclose(fptr);
    postnr->areas = areas;
    postnr->n = size;
    return postnr;
}

void collisions(codes *postnr) {
    int size = postnr->n;
    int mx = 20;
    int cols[mx];
    for (int i = 0; i < mx; i++) cols[i] = 0;
    
    int total = 0;
    for (int i = 0; i < size; i++) {
        if (postnr->areas[i].name != NULL) {
            int ideal = hash(postnr->areas[i].zip, size);
            int distance = ((i - ideal + size) % size);  // distance
            if (distance < mx) cols[distance]++;
            total++;
        }
    }
    
    printf("Total entries: %d, Table size: %d\n", total, size);
    printf("Probe distance distribution:\n");
    for (int i = 0; i < mx; i++) {
        if (cols[i] > 0)
            printf("%d probes: %d entries\n", i, cols[i]);
    }
    printf("\n");
}

void codes_print(codes *postnr){
    for (int i = 0; i < postnr->n; i++){
        area current = postnr->areas[i];
        if (current.name == (char *) 0) continue;
        printf("slot %d: name=%s, zip=%d, pop=%d\n", i, current.name, current.zip, current.pop);
    }
}

area* codes_lookup(codes *postnr, int zip) {
    int size = postnr->n;
    int index = hash(zip, size);
    int count = 0;
    while (count++ < size) {
        area *current = &postnr->areas[index];
        if (current->name == NULL) return NULL;  // empty slot = not found
        if (current->zip == zip) return current;
        index = (index + 1) % size;
    }
    return NULL;
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
    
	
	collisions(postnr);
	codes_print(postnr);
}