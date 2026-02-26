#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AREAS 100000
#define BUFFER 200

typedef struct area {
    char *name;
    char *zip;
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
        a.zip = strtok(copy, ",");
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
		printf("name=%s\t zip=%s\t pop=%d\n", a.name, a.zip, a.pop);
	}
}

area* codes_linear_search(codes *postnr, char *zip){
	int i = 0;
	int length = postnr->n;
	area *areas = postnr->areas;
	while (i < length && strcmp(zip, areas[i].zip) != 0){
		i++;
	}
	if (i == postnr->n){
		return NULL;
	}
	return &postnr->areas[i];
}


area* codes_binary_search(codes *postnr, char *zip){
	int lo = 0;
	int hi = postnr->n-1;
	area *areas = postnr->areas;
	while (lo <= hi){
		int mid = lo/2 + hi/2;
		int cmp = strcmp(zip, areas[mid].zip);
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
		printf("name=%s\t zip=%s\t pop=%d\n", a->name, a->zip, a->pop);
	}
}

int main(){
	codes *postnr = read_postcodes("zipcodes.csv");
	area *a = codes_binary_search(postnr, "753 20");
	area_print(a);
	
	a = codes_binary_search(postnr, "582 20");
	area_print(a);

	a = codes_binary_search(postnr, "214 20");
	area_print(a);
	
	a = codes_binary_search(postnr, "no");
	area_print(a);
	// codes_print(postnr);
}