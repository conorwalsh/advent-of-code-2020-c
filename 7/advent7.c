/*
 * Advent of Code challenge 7
 *
 * Conor Walsh 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

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

	// Count passports
	int passports = 0;
	for (int i = 0; i<count; i++){
		if(all[i][0]=='\n'){
			passports++;
		}
	}
	passports++;

	// Create empty array of char arrays
	char formatted[passports][255];
	for (int i = 0; i<passports; i++){
		for (int j = 0; j<255; j++){
			formatted[i][j]='\0';
		}
	}

	// Get passports on one line
	int passdone = 0;
	for (int i = 0; i<count; i++){
		if(all[i][0]!='\n'){
			strcat(formatted[passdone],all[i]);
			for (int j = 0; j<255; j++){
				if (formatted[passdone][j]=='\n'){
					formatted[passdone][j]=' ';
				}
			}
		}
		else{
			passdone++;
		}
	}

	// Loop through each passport and count fields (: character)
	int ans = 0;
	for (int i = 0; i<passports; i++){
		char* counttmp = formatted[i];
		int ccount = 0;
		while(counttmp != NULL){                                                                                                                       
			counttmp = strchr(counttmp, ':');                                                                                                           
		        if( counttmp ) {
				counttmp++;
				ccount++;
			}                                                                                                
		}
		// If fields 8 passport is valid
		if (ccount==8){
			ans++;
		}
		// If fields 7 but only missing cid
		else if (ccount==7){
			if (strstr(formatted[i], "ecl") != NULL && strstr(formatted[i], "pid") != NULL && strstr(formatted[i], "eyr") != NULL && strstr(formatted[i], "hcl") != NULL && strstr(formatted[i], "byr") != NULL && strstr(formatted[i], "iyr") != NULL && strstr(formatted[i], "hgt") != NULL){
				ans++;
			}
		}
	}

	// Print answer and exit
	printf("Valid Passports: %d\n", ans);
	return 0;
}
