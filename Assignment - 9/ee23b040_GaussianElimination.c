/*****************************************************************************************************

RollNo,Name : EE23B040,Madhav T
Date 		: 13/10/2023
Description : This program calculates the roots of a given set of linear equations using the gaussian
			  elimination method.
Input		: Takes 2 command line arguments
			  -> The file path
			  -> Number of unknowns
Output		: Prints all N unknowns seperated by a space.

*****************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void gauss(double** A, double* B, int n, double* X, double tol);
void pivot(double** A, double* B, double* S, int n, int k);
void eliminate(double** A, double* S, int n, double* B, double tol, int* er);
void substitute(double** A, int n, double* B, double* X);


int main (int argc, char *argv[]) {

	int n = atoi(argv[2]);
	FILE* fptr = fopen(argv[1], "r");
	double tol = 0.00001;							// Tolerance only to ensure no extreme values present

	double** A = malloc(n*sizeof(double*));
	double* B = malloc(n*sizeof(double));
	double* X = malloc(n*sizeof(double));

	for(int i=0; i < n; i++){
		A[i] = malloc(n*sizeof(double));			// Creating a 2D array
	}

	for(int i=0; i < n; i++){						// Storing the values from the file
		for(int j=0; j < n; j++){
			fscanf(fptr, "%lf", &A[i][j]);
		}
		fscanf(fptr, "%lf", &B[i]);
	}

/*
	for(int i=0; i < n; i++){						// Was used to check matrix A (debugging)
		for(int j=0; j < n; j++){
			printf("%lf ", A[i][j]);
		}
		printf("\n");
	}
	for(int i=0; i < n; i++){
		printf("%lf", B[i]);
		printf("\n");
	}
*/


	gauss(A, B, n, X, tol);


	for(int i=0; i < n; i++){
		free(A[i]);
	}
	free(A);
	free(X);
	free(B);
	return 0;
}



void gauss(double** A, double* B, int n, double* X, double tol){
	double* S = malloc(n*sizeof(double));
	int er = 0;

	for(int i=0; i < n; i++){						// Stores the max value of coefficients in a certain row
		S[i] = fabs(A[i][0]);
		for(int j=1; j < n; j++){
			if(S[i] < fabs(A[i][j])){
				S[i] = A[i][j];
			}
		}
	}

	eliminate(A, S, n, B, tol, &er);


	if(er != -1){
		substitute(A, n, B, X);						// Back substitute only when error has not occured
	}
	else{
		printf("error!\n");
	}
}



void eliminate(double** A, double* S, int n, double* B, double tol, int* er){
	for(int k=0; k < n-1; k++){							// Creates the upper triangular matrix from original matrix

		pivot(A, B, S, n, k);

		if(fabs(A[k][k]/S[k]) < tol){
			*er = -1;
			break;
		}
		for(int i=k+1; i < n; i++){
			double factor = A[i][k]/A[k][k];

			for(int j=k; j < n; j++){
				A[i][j] -= factor*A[k][j];
			}
			B[i] -= factor*B[k];

		}
	}
	if(fabs(A[n-1][n-1]/S[n-1]) < tol){
		*er = -1;
	}

}



void pivot(double** A, double* B, double* S, int n, int k){
	int p = k;
	double buf;
	int big = fabs(A[k][k]/S[k]);

	for(int i=k; i < n; i++){
		buf = fabs(A[i][k]/S[i]);
		if(buf > big){
			big = buf;
			p = i;
		}
	}

	if(p != k){										// Swapping the rows only when the value of p changes
		for(int i=k; i < n; i++){
			buf = A[p][i];
			A[p][i] = A[k][i];
			A[k][i] = buf;
		}

		buf = B[p];
		B[p] = B[k];
		B[k] = buf;

		buf = S[p];
		S[p] = S[k];
		S[k] = buf;
	}
}



void substitute(double** A, int n, double* B, double* X){
	X[n-1] = B[n-1]/A[n-1][n-1];

	for(int i=n-2; i >= 0; i--){
		double sum = 0;
		for(int j=i+1; j < n; j++){
			sum += A[i][j]*X[j];
		}
		X[i] = (B[i] - sum)/A[i][i];					// Calculates all the x values from n till 0
	}

	for(int i=0; i < n; i++){
		printf("%lf ", X[i]);
	}
	printf("\n");

}