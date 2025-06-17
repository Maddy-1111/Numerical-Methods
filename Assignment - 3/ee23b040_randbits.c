/*****************************************************************************************************************

RollNo,Name : EE23B040,Madhav T
Date 		: 25/8/2023
Description : Takes in one or more than one flags and outputs a random bit sequence in a file (given -n as a flag)
  			  or calculates the hamming distance between 2 files (given -h as a flag).
Inputs 		: Takes the flag -n followed by a positive integer (optionally adding -s followed by a seed or adding -t).
			  Takes the flag -h followed by 2 file paths seperated by a space.
Outputs 	: Creates a file called "randbits.c" which contains the charecters "1" or "0" if -n flag is provided
			  Prints the hamming distance of the 2 given files if -h flag is provided

*****************************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void randombits (int num); // Generates a random bit sequence of length given by used

int hamming(char *fpath1, char *fpath2); // Returns the hamming dist of the 2 files passed


int main (int argc, char *argv[]) {

	char flag;
	int gen_bits = 0;
	int num;

	while ((flag = getopt(argc, argv, "n:s:th:")) != -1) {
		switch (flag) {
			case 'n':
				gen_bits = 1;
				num = atoi(argv[optind-1]);
				break;
			case 's':
				srand(atoi(argv[optind-1]));
				break;
			case 't':
				srand((int) time(NULL));
				break;
			case 'h':
				printf("Hamming distance is %d\n", hamming(argv[optind-1], argv[optind]));
				break;
		}
	}

	if (gen_bits == 1)
		randombits (num);

	return 0;
}



void randombits (int num) {

	FILE *fptr;
	fptr = fopen ("randbits.txt","wb");
	
	char *rand_ptr = (char*)malloc(num*sizeof(char));

	for (int i=0; i<num; i++){
		int rand_num = rand();

		if (rand_num%2 == 0)
			rand_ptr[i] = '0';
		else
			rand_ptr[i] = '1';
	}

	fwrite(rand_ptr, sizeof(char), num, fptr);

	fclose(fptr);
}



int hamming (char *fpath1, char *fpath2) {
	FILE *fptr1;
	FILE *fptr2;
	fptr1 = fopen(fpath1, "rb");
	fptr2 = fopen(fpath2, "rb");

	char bit1;
	char bit2;
	int count = 0;

	while((bit1=fgetc(fptr1)) != -1 && (bit2=fgetc(fptr2)) != -1) {
		if (bit1 != bit2)
			count += 1;
	}

	fclose(fptr1);
	fclose(fptr2);

	return count;
}