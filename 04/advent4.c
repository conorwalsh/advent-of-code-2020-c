/*
 * Advent of Code challenge 4
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
	for (int d = 0; d<count; d++){
		// Get each part of line seperated by space
		char *parts[3];
		char *token = strtok(all[d], " ");
	        int z = 0;
	        while (token != NULL){
	                parts[z] = token;
			token = strtok(NULL, " ");
	                z++;
	        }
		
		// Get the first and last positions
		int firstn = 0;
		int secondn = 0;
		char *part1 = strtok(parts[0], "-");
		sscanf(part1, "%d", &firstn);
		firstn--;
		part1 = strtok(NULL, "-");
		sscanf(part1, "%d", &secondn);
		secondn--;
		
		// Get the required character (first char in array)
		char let = parts[1][0];

		// Count occurances at positons
		int occ = 0;
		if (parts[2][firstn]==let)
			occ++;
		if (parts[2][secondn]==let)
			occ++;
		
		// If only occured once then increment answer
		if(occ==1){
			ans++;
		}
	}

	// Print answer and exit
	printf("Valid Passwords: %d\n", ans);
	return 0;
}
