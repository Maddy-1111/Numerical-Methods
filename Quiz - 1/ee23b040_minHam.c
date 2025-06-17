/*****************************************************************************************************************

RollNo,Name : EE23B040,Madhav T
Date 		: 15/9/2023
Description : This program takes 4 inputs (N, Nseed, M, Mseed) as terminal commands. it creates 2
			  strings (mbits, nbits) in which random numbers of length (M, N) are generated using
			  seeds (Mseed and Nseed).
			  It then creates 2 files(Mfile.dat, Nfile.dat) in which the 2 strings are inserted.
			  It also calculates the least hamming distance between the two random bit sequences and prints it out.


*****************************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main (int argc, char *argv[]) {

	int N = atoi(argv[1]);
	int Nseed = atoi(argv[2]);
	int M = atoi(argv[3]);
	int Mseed = atoi(argv[4]);

	if(M > N){
		printf("error");
	}
	else{

		srand(Nseed);
		char *nbits = (char*)malloc(N*sizeof(char));

		for (int i=0; i<N; i++){
			int rand_num1 = rand();

			if (rand_num1%2 == 0)
				nbits[i] = '0';
			else
				nbits[i] = '1';
		}

		srand(Mseed);
		char *mbits = malloc(M*sizeof(char));

		for (int i=0; i<M; i++){
			int rand_num2 = rand();

			if (rand_num2%2 == 0)
				mbits[i] = '0';
			else
				mbits[i] = '1';
		}



		FILE *fptrM;
		fptrM = fopen ("Mfile.dat","w");
		for(int i = 0; i < M; i++){
			fputc(mbits[i],fptrM);
			fputc(32, fptrM);
		}
		fclose(fptrM);

		FILE *fptrN;
		fptrN = fopen ("Nfile.dat","w");
		for(int i = 0; i < N; i++){
			fputc(nbits[i],fptrN);
			fputc(32, fptrN);
		}
		fclose(fptrM);
		


		int hamm_dist = M;
		int hamm_loc = 0;

		for (int i=0; i < N-M; i++){

			int temp = 0;
			for (int j=0; j < M; j++){
				if(mbits[j] != nbits[i+j])
					temp++;
			}

			if(hamm_dist > temp){
				hamm_dist = temp;
				hamm_loc = i;
			}
		}

		printf("%d %d \n", hamm_loc, hamm_dist);
	}

	return 0;
}