/*
 * Advent of Code challenge 11
 *
 * Conor Walsh 2020
 *
 * Input must end in newline or will go into infinite loop
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
		// Array to store unique letters seen
		char let[30] = { 0 };
		// Store size of above array
		int curlet = 0;
		// Set initial letter
		let[0] = all[d][0];
		// If first character is newline go to next group
		while (all[d][0]!='\n'){
			int i = 0;
			// If character is newline go to next person
			while(all[d][i]!='\n'){
				// Check every letter to see if its not in list
				int found = 0;
				for(int j = 0; j<=curlet; j++){
					if(all[d][i]==let[j]){
						found=1;
					}
				}
				// If not in list add to list
				if (found==0){
					curlet++;
					let[curlet]=all[d][i];
				}
				i++;
			}
			// Only increment if wont overflow array
			if (d<count-1)
				d++;
		}
		// Add numbe of letters to answer (curlet starts at 0 so add 1)
		ans+=(curlet+1);
	}

	// Print answer and exit
	printf("Sum: %d\n", ans);
	return 0;
}
