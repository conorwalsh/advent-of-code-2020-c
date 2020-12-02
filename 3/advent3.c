/*
 * Advent of Code challenge 3
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

	// Open file again to read lines
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
		
		// Get the min and max count
		int min = 0;
		int max = 0;
		char *part1 = strtok(parts[0], "-");
		sscanf(part1, "%d", &min);
		part1 = strtok(NULL, "-");
		sscanf(part1, "%d", &max);
		
		// Get the required character (first char in array)
		char let = parts[1][0];

		// Count the occurances of the character in the array
		char* counttmp = parts[2];
		int ccount = 0;
		while(counttmp != NULL){                                                                                                                       
			counttmp = strchr(counttmp, let);                                                                                                           
		        if( counttmp ) {
				counttmp++;
				ccount++;
			}                                                                                                
		}
		
		// If the count is between min and max increment answer
		if(ccount>=min&&ccount<=max){
			ans++;
		}
	}

	// Print answer and exit
	printf("Valid Passwords: %d\n", ans);
	return 0;
}
