/***********************************************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 21/09/2023
Description : This code takes in 1 input txt file and creates 1 output txt file.
			  (Requires math module while running)
			  It creates an array of the input planets where each index is equal to the planet number
			  It then links any 2 planets by replacing both the array values to a new value which is
			  the lower out of the 2 existing values, and then replaces the values of any index who's value 
			  is the same as the larger of the 2 values to the same lower value.
			  Once this operation is performed, a "1" is appended to the output file.
			  If the 2 values checked initially are equal, no operation is performed and a "0" is appended
			  to the output file.
			  finally, the runtime is appended on the next line using the clock() function.

***********************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>								// For using "clock" function
#include<math.h>								// For using "ceil" function


int main(int argc, char* argv[]) {

	clock_t start, end;
	double runtime;
	start = clock();

	FILE* finp = fopen(argv[1], "r");
	FILE* fout = fopen("ee23b040_quiz2_q1_output.txt", "w");

	int N;										// aka number of Planets
	int M;										// aka number of Requests

	fscanf(finp, "%d", &N);
	fscanf(finp, "%d", &M);

	int* realms = malloc(N*sizeof(int));

	for(int i=0; i < N; i++)
		realms[i] = i;							// Creating an array of all Planets

	for(int i=0; i < M; i++){
		int node1;
		int node2;
		fscanf(finp, "%d", &node1);
		fscanf(finp, "%d", &node2);

		if(realms[node2] == realms[node1]){
			fprintf(fout, "%d", 0);
			continue;
		}

		fprintf(fout, "%d", 1);

		if(realms[node1] < realms[node2]){
			int extention = realms[node2];				// "extention" is a buffer(temporary) variable
			for(int j = realms[node1]; j < N; j++){		// Starting value of j is not 0 to optimise the number of operations
				if(realms[j] == extention)
					realms[j] = realms[node1];
			}
		}
		else{											// To ensure planets always get mapped down 
			int extention = realms[node1];				// i.e if 1 and 6 are linked, 6 becomes 1 and not the other way
			for(int j = realms[node2]; j < N; j++){
				if(realms[j] == extention)
					realms[j] = realms[node2];
			}
		}
	}


	end = clock();
	runtime = (double)(end - start)/CLOCKS_PER_SEC;				// Converting cpu clock time into seconds
	fprintf(fout, "\n%d ms", (int)ceil(runtime*1000));			// Rounding time upto the nearest(greater) integer

	fclose(finp);
	fclose(fout);
	free(realms);
	return 0;
}