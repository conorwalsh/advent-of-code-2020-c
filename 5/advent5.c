/*
 * Advent of Code challenge 5
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
	int ans = 0;
	int posx = 0;
	int posy = 0;
	int mx = 3;
	int my = 1;
	// Get width of file (-1 for newline)
	int width = strlen(all[0])-1;
	// Check for tree on every line at specified position (starting at 1)
	for (int d = 1; d<count; d++){
		posx += mx;
		posy += my;
		// To allow infinite field wrap around if outside input size
		if(posx>=width){
			posx-=width;
		}

		if (all[posy][posx]=='#'){
			ans++;
		}
	}

	// Print answer and exit
	printf("Trees: %d\n", ans);
	return 0;
}
