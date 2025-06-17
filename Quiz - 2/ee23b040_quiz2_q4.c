/***********************************************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 23/09/2023
Description : This code takes in 1 input txt file and creates 1 output txt file.
  			  (Requires math module while running)
			  It creates 2 arrays, one containing the parent to each of the planets and the other containing 
			  the weight of respective heads.
			  It then links 2 planets by checking the weight of the respective heads and adding the tree with
			  a lesser weight as a branch of the other tree.
			  Once this operation is performed, a "1" is appended to the output file.
			  If the 2 values of the heads are equal, no operation is performed and a "0" is appended
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
	FILE* fout = fopen("ee23b040_quiz2_q4_output.txt", "w");

	int N;										// aka number of Planets
	int M;										// aka number of Requests

	fscanf(finp, "%d", &N);
	fscanf(finp, "%d", &M);

	int* realms = malloc(N*sizeof(int));
	int* weight = malloc(N*sizeof(int));

	for(int i=0; i < N; i++){
		realms[i] = i;							// Creating an array of all Planets with weights 1 each
		weight[i] = 1;
	}

	for(int i=0; i < M; i++){
		int node1;
		int node2;
		fscanf(finp, "%d", &node1);
		fscanf(finp, "%d", &node2);

		while(realms[node1] != node1){			// Traversing to the head of each planet
			node1 = realms[node1];
		}
		while(realms[node2] != node2){
			node2 = realms[node2];
		}

		if(node1 == node2){
			fprintf(fout, "%d", 0);
			continue;
		}

		fprintf(fout, "%d", 1);

// Checking the weight and accordingly adding the smaller tree as a branch to the larger tree

		if(weight[node1] >= weight[node2]){
			realms[node2] = node1;
			weight[node1] += weight[node2];
		}
		else{
			realms[node1] = node2;
			weight[node2] += realms[node1];
		}
	}


	end = clock();
	runtime = (double)(end - start)/CLOCKS_PER_SEC;				// Converting cpu clock time into seconds
	fprintf(fout, "\n%d ms", (int)ceil(runtime*1000));			// Rounding time upto the nearest(greater) integer

	fclose(finp);
	fclose(fout);
	free(realms);
	free(weight);
	return 0;
}