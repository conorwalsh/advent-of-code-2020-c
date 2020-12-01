/*
 * Advent of Code challenge 2
 *
 * Conor Walsh 2020
 */

#include <stdio.h>

// Max line char array length
#define MAXCHAR 10

int main() {
	// Setup file
	FILE *fp;
	char str[MAXCHAR];
	// Set file name as desired
	char* filename = "in.txt";

	// Open file as read and check exists
	fp = fopen(filename, "r");
	if (fp == NULL){
		printf("Could not open file %s",filename);
		return 1;
	}
	// Count lines (needed for array sizes
     	int count=0;
	while (fgets(str, MAXCHAR, fp) != NULL){
		count++;
	}
	fclose(fp);

	// Open file again to read numbers (no need to check exists)
	fp = fopen(filename, "r");
	int all[count];
	int i = 0;
	while (fgets(str, MAXCHAR, fp) != NULL){
		int tmp;
		sscanf(str, "%d", &tmp);
		all[i] = tmp;
		i++;
	}
	fclose(fp);

	// Loop through and check array against itself using 2 for loops
	int ans = 0;
	for (int j = 0; j < count; j++) {
		for (int k = 0; k < count; k++) {
			for (int l = 0; l < count; l++) {
				if (all[j] + all[k] + all[l] == 2020){
					ans = all[j] * all[k] * all[l];
					// Break out of loop if answer found (faster)
					break;
				}
			}
			// Break out of loop if answer found (faster)
			if (ans != 0){
				break;
			}
		}
		// Break out of loop if answer found (faster)
		if (ans != 0){
			break;
		}
	}
	
	// Print answer and exit
	printf("%d\n", ans);
	return 0;
}
