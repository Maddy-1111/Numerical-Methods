/***********************************************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 22/09/2023
Description : This code takes in 1 input txt file and creates 1 output txt file.
			  (Requires math module while running)
			  It creates a structure containing a weight and a struct pointer to traverse up the struct tree
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


struct realm {
	int weight;
	struct realm* parent;
};


int main(int argc, char* argv[]) {

	clock_t start, end;
	double runtime;
	start = clock();

	FILE* finp = fopen(argv[1], "r");
	FILE* fout = fopen("ee23b040_quiz2_q3_output.txt", "w");

	int N;										// aka number of Planets
	int M;										// aka number of Requests

	fscanf(finp, "%d", &N);
	fscanf(finp, "%d", &M);

	struct realm** realms = malloc(N*sizeof(struct realm*));	// Creating an array containing structs for each polanet

	for(int i=0; i < N; i++){
		realms[i] = malloc(sizeof(struct realm));		// Allocating memory for the structures
		realms[i]->weight = 1;
		realms[i]->parent = realms[i];					// Setting every planet as its own head initially
	}

	for(int i=0; i < M; i++){
		int node1;
		int node2;
		fscanf(finp, "%d", &node1);
		fscanf(finp, "%d", &node2);

// I have not created a temp variable to traverse the tree in the following while loops
// Instead, I directly traversed the node (changing it)
// This reduced the space used and reduced the length of trees formed (optimisation)

		while(realms[node1] != realms[node1]->parent){
			realms[node1] = realms[node1]->parent;
		}
		while(realms[node2] != realms[node2]->parent){
			realms[node2] = realms[node2]->parent;
		}

		if(realms[node1] == realms[node2]){
			fprintf(fout, "%d", 0);
			continue;
		}

		fprintf(fout, "%d", 1);

// Checking the weight and accordingly adding the smaller tree as a branch to the larger tree

		if(realms[node1]->weight >= realms[node2]->weight){		
			realms[node2]->parent = realms[node1];
			realms[node1]->weight += realms[node2]->weight;
		}
		else{
			realms[node1]->parent = realms[node2];
			realms[node2]->weight += realms[node1]->weight;
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