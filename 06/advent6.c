/*
 * Advent of Code challenge 6
 *
 * Conor Walsh 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max line char array length
#define MAXCHAR 100

int main(int argc, char **argv) {
	// Check for file input, error if none
	if (argc != 2) {
		fprintf(stderr, "usage: %s <file>\n",argv[0]);
		exit(1);
	}

	// Setup file
	FILE *fp;
	char str[MAXCHAR];
	char* filename = argv[1];

	// Open file as read and check exists
	fp = fopen(filename, "r");
	if (fp == NULL){
		printf("Could not open file %s\n",filename);
		return 1;
	}
	// Count lines (needed for array sizes)
     	int count=0;
	while (fgets(str, MAXCHAR, fp) != NULL){
		count++;
	}
	fclose(fp);

	// Open file again to lines (no need to check exists)
	fp = fopen(filename, "r");
	char *all[count];
	size_t len = 0;
	for(int i = 0; i < count; i++){
		all[i] = NULL;
		len = 0;
		getline(&all[i], &len, fp);
	}
	fclose(fp);

	// For each line check parameters
	// Change ans to long to prevent overflow
	long ans = 0;
	int my[] = {1, 1, 1, 1, 2};
	int mx[] = {1, 3, 5, 7, 1};
	// Get width of file (-1 for newline)
	int width = strlen(all[0])-1;
	// Check 5 moves
	for (int i = 0; i<5; i++){
		int trees = 0;
		int posx = 0;
		int posy = 0;
		// Check for tree on every line at specified position (starting at 1)
		for (int d = 0; d<count; d+=my[i]){
			// To allow infinite field wrap around if outside input size
			if(posx>=width){
				posx-=width;
			}

			if (all[posy][posx]=='#'){
				trees++;
			}
			posx += mx[i];
			posy += my[i];
		}
		if (i==0){
			ans = (long)trees;
		}
		else{
			ans *= (long)trees;
		}
		printf("Trees (%d): %d\n",i,trees);
	}

	// Print answer and exit
	printf("Ans: %ld\n", ans);
	return 0;
}
