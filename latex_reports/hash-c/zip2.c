#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AREAS 100000
#define BUFFER 200

typedef struct area {
    char *name;
    int zip;
    int pop;
} area;

typedef struct codes {
    area *areas;
    int n;
} codes;

codes *read_postcodes(char *file) {
    codes *postnr = (codes*) malloc(sizeof(codes));
    area *areas = (area*) malloc(sizeof(area)*AREAS);
    FILE *fptr = fopen(file, "r");
    int k = 0;
    char *lineptr = malloc(sizeof(char)*BUFFER);
    size_t n = BUFFER;
    while((k < AREAS) && (getline(&lineptr, &n, fptr) > 0)) {
        char *copy = (char*) malloc(sizeof(char)*n);
        strcpy(copy, lineptr);
        area a;
        char *zip = strtok(copy, ",");
		a.zip = atoi(zip)*100 + atoi(zip+3);
        a.name = strtok(NULL, ",");
        a.pop = atoi(strtok(NULL, ","));
        areas[k++] = a;
    }
    fclose(fptr);
    postnr->areas = areas;
    postnr->n = k;
    return postnr;
}

void codes_print(codes *postnr){
	area *areas = postnr->areas;
	int length = postnr->n;
	for (int i = 0; i < length; i++){
		area a = areas[i];
		printf("name=%s\t zip=%d\t pop=%d\n", a.name, a.zip, a.pop);
	}
}

area* codes_linear_search(codes *postnr, int zip){
	int i = 0;
	int length = postnr->n;
	area *areas = postnr->areas;
	while (i < length && zip != areas[i].zip){
		i++;
	}
	if (i == postnr->n){
		return NULL;
	}
	return &postnr->areas[i];
}


area* codes_binary_search(codes *postnr, int zip){
	int lo = 0;
	int hi = postnr->n-1;
	area *areas = postnr->areas;
	while (lo <= hi){
		int mid = lo/2 + hi/2;
		int cmp = zip - areas[mid].zip;
		if (cmp < 0){
			hi = mid - 1; // turn left
		}
		else if (cmp > 0){
			lo = mid + 1; // turn right
		}
		else{
			return &areas[mid];
		}
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

void collisions(codes *postnr, int mod) {
    int mx = 20;
    int data[mod];
    int cols[mx];
    for (int i = 0; i < mod; i++) data[i] = 0;
    for (int i = 0; i < mx; i++) cols[i] = 0;
    for (int i = 0; i < postnr->n; i++) {
        if (postnr->areas[i].name != NULL) {  // only count actual entries
            int index = (postnr->areas[i].zip)%mod;
            data[index]++;
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
        for (int i = 0; i < postnr->n; i++) {
            if (postnr->areas[i].name != NULL && (postnr->areas[i].zip) % mod == bucket) {
                printf("bucket %d: %s (zip=%d)\n", bucket, postnr->areas[i].name, postnr->areas[i].zip);
            }
        }
    }
    printf("\n");
}

int main(){
	codes *postnr = read_postcodes("zipcodes.csv");
	area *a = codes_binary_search(postnr, 75320);
	area_print(a);
	
	a = codes_binary_search(postnr, 58220);
	area_print(a);

	a = codes_binary_search(postnr, 21420);
	area_print(a);
	
	a = codes_binary_search(postnr, 0);
	area_print(a);

	collisions(postnr, 17);
	// codes_print(postnr);
}