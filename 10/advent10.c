/*
 * Advent of Code challenge 10
 *
 * Conor Walsh 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max line char array length
#define MAXCHAR 15

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
	char *passes[count];
	size_t len = 0;
	for(int i = 0; i < count; i++){
		passes[i] = NULL;
		len = 0;
		getline(&passes[i], &len, fp);
	}
	fclose(fp);
	
	// int array to mark passes found	
	int maxsid = (127*8)+7;
	int passi[maxsid];
	for (int i = 0; i<maxsid; i++){
		passi[i] = 0;
	}
	// Loop through all passes	
	for (int i = 0; i<count; i++){
		// Get the row and seat info and convert to binary
		char rowc[7];
		char seatc[3];
		for (int j = 0; j<7; j++){
			if (passes[i][j]=='F'){
				rowc[j] = '0';
			}
			else{
				rowc[j] = '1';
			}
		}
		for (int j = 0; j<3; j++){
			if (passes[i][j+7]=='L'){
				seatc[j] = '0';
			}
			else{
				seatc[j] = '1';
			}
		}
		// Convert row and seat from char to int (binary)
		int rowb = 0;
		int row = 0;
		sscanf(rowc, "%d", &rowb);
		int seatb = 0;
		int seat = 0;
		sscanf(seatc, "%d", &seatb);
		// Convert row and seat from binary to decimal
	        int base = 1;
		while (rowb > 0){
			int rem = rowb % 10;
			row = row + rem * base;
			rowb /= 10 ;
			base *= 2;
		}
		base = 1;
		while (seatb > 0){
			int rem = seatb % 10;
			seat = seat + rem * base;
			seatb /= 10 ;
			base *= 2;
		}
		// Get seat id
		int sid = (row * 8) + seat;
		// If the current seat id is higher than answer then update the answer
		passi[sid] = 1;
	}
	// Loop through all seats to check for an empty seat with an occupied seat each side
	int ans = 0;
	for (int i = 1; i<(maxsid-1); i++){
		if(passi[i]==0&&passi[i-1]==1&&passi[i+1]==1){
			ans = i;
			// If found dont bother checking rest
			break;
		}
	}

	// Print answer and exit
	printf("Your Seat ID: %d\n", ans);
	return 0;
}
