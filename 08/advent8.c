/*
 * Advent of Code challenge 8
 *
 * Conor Walsh 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * This problem is not very well suited to C
 * This is not very good code
 * I did this to challenge myself (Python would suit this problem very well)
 */

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

	// Count all passports
	int passports = 0;
	for (int i = 0; i<count; i++){
		if(all[i][0]=='\n'){
			passports++;
		}
	}
	passports++;

	// Setup an empty array of char arrays
	char formatted[passports][255];
	for (int i = 0; i<passports; i++){
		for (int j = 0; j<255; j++){
			formatted[i][j]='\0';
		}
	}

	// Get all passport info into one line (no \n)
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

	// Check every passport
	int ans = 0;
	for (int i = 0; i<passports; i++){
		// Count fields
		char* counttmp = formatted[i];
		int ccount = 0;
		while(counttmp != NULL){                                                                                                                       
			counttmp = strchr(counttmp, ':');                                                                                                           
		        if( counttmp ) {
				counttmp++;
				ccount++;
			}                                                                                                
		}
		// Check if missing cid (North Pole)
		int np = 0;
		if( strstr(formatted[i], "cid")==NULL ){
			np = 1;
		}
		// Split into fields (split by space)
		char *parts[8];
		char *token = strtok(formatted[i], " ");
		int z = 0;
		while (token != NULL){
			parts[z] = token;
			token = strtok(NULL, " ");
			z++;
		}
		// Check every field
		int iinval = 0;
		for (int j = 0; j<ccount; j++){
			// Split into key and data
			char *ki[2];
			char *tokeni = strtok(parts[j], ":");
			int x = 0;
			while (tokeni != NULL){
				ki[x] = tokeni;
				tokeni = strtok(NULL, ":");
				x++;
			}
			// Check eye color is one of the options
			if (strstr(ki[0], "ecl")!=NULL){
				if (strstr(ki[1], "amb")==NULL && strstr(ki[1], "blu")==NULL && strstr(ki[1], "brn")==NULL && strstr(ki[1], "gry")==NULL && strstr(ki[1], "grn")==NULL && strstr(ki[1], "hzl")==NULL && strstr(ki[1], "oth")==NULL){
					iinval++;
				}
			}
			// Check birth year
			else if (strstr(ki[0], "byr")!=NULL){
				if(atoi(ki[1])<1920||atoi(ki[1])>2002){
					iinval++;
				}
			}
			// Check issue year
			else if (strstr(ki[0], "iyr")!=NULL){
				if(atoi(ki[1])<2010||atoi(ki[1])>2030){
					iinval++;
				}
			}
			// Check expiry year
			else if (strstr(ki[0], "eyr")!=NULL){
				if(atoi(ki[1])<2020||atoi(ki[1])>2030){
					iinval++;
				}
			}
			// Check height
			else if (strstr(ki[0], "hgt")!=NULL){
				// cm
				if (strstr(ki[1], "cm")!=NULL){
					ki[strlen(ki[1])-2]='\0';
					int hgt=atoi(ki[1]);
					if (hgt<150||hgt>193){
						iinval++;
					}
				}
				// in
				else if (strstr(ki[1], "in")!=NULL){
					ki[strlen(ki[1])-2]='\0';
					int hgt=atoi(ki[1]);
					if (hgt<59||hgt>76){
						iinval++;
					}
				}
				// no unit
				else {
					iinval++;
				}
			}
			// Check hair color
			else if (strstr(ki[0], "hcl")!=NULL){
				if( ki[1][0]!='#'){
					iinval++;
				}
				else if (strlen(ki[1])!=7){
					iinval++;
				}
				ki[1]++;
				for (int c = 0; c<strlen(ki[1]); c++){
					if (!isxdigit(ki[1][c])){
						iinval++;
					}
				}
			}
			// Check passport id
			else if (strstr(ki[0], "pid")!=NULL){
				if( strlen(ki[1])!=9){
					iinval++;
				}
				for (int c = 0; c<strlen(ki[1]); c++){
					if (!isdigit(ki[1][c])){
						iinval++;
					}
				}

			}
		}
		// Increment if 8 fields all correct
		if (ccount==8&&iinval==0){
			ans++;
		}
		// Increment if 7 fields all correct (North Pole)
		else if (ccount==7&&iinval==0&&np==1){
			ans++;
		}
	}

	// Print answer and exit
	printf("Valid Passports: %d\n", ans);
	return 0;
}
