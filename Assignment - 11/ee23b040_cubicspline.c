/***********************************************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 23/10/2023
Inputs		: Order of approximation(number of sample points taken - 1), x value to be found
Outputs		: Value of x which was required
Description : This program uses the Cubic-spline interpolation method to fit a curve onto a given 
			  set of points,it then caluclate the value of this curve at a required x.
			  The cubic-spline method works by creating a unique cubic between every 2 sample points,
			  it ensures the final curve is continuous, differentiable and double differentiable even
			  though it is defined piece-wise.
			  This code uses an optimised algorithm to form and solve n+1 equations rather than 4n equations
			  for the n cubics required.

***********************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


void gauss(double** A, double* B, int n, double* X, double tol);
void pivot(double** A, double* B, double* S, int n, int k);
void eliminate(double** A, double* S, int n, double* B, double tol, int* er);
void substitute(double** A, int n, double* B, double* X);
double f(double x);												// function as given in Moodle
void interpolate(double* F, double* X, double xreq, double xstart, double xend, int order);


int main(int argc, char*argv[]) {

	double tol = 0.00001;								// Tolerance only to ensure no extreme values present
	int order = atoi(argv[1]);
	double xstart = -1;
	double xend = 1;
	double xreq = atof(argv[2]);

	double* X = malloc((order+1)*sizeof(double));

	for(int i=0; i < order+1; i++){								// Creating the array of sample points
		X[i] = xstart + ((double)i/(order))*(xend - xstart);
	}

	double** A = malloc((order+1)*sizeof(double*));
	double* B = malloc((order+1)*sizeof(double));
	double* F = malloc((order+1)*sizeof(double));				// F will store the value of f''
																// (2nd derevative) at every sample point
	for(int i=0; i < (order+1); i++){
		A[i] = calloc((order+1), sizeof(double));
	}


	A[0][0] = 1;
	B[0] = 0;
	for(int i=1; i < order;  i++){								// Creating the simultaneous equations
		A[i][i-1] = X[i] - X[i-1];
		A[i][i] = 2*(X[i+1] - X[i-1]);
		A[i][i+1] = X[i+1] - X[i];
		B[i] = 6*(f(X[i+1]) - f(X[i]))/(X[i+1] - X[i]) + 6*(f(X[i-1]) - f(X[i]))/(X[i] - X[i-1]);
	}
	A[order][order] = 1;
	B[order] = 0;

/*
	for(int i=0; i < order+1; i++){							// Was used to check matrix A,B (debugging)
		for(int j=0; j < order+1; j++){
			printf("%lf ", A[i][j]);
		}
		printf("\n");
	}
	for(int i=0; i < order+1; i++){
		printf("%lf", B[i]);
		printf("\n");
	}
*/

	gauss(A, B, order+1, F, tol);
	interpolate(F, X, xreq, xstart, xend, order);


	for(int i=0; i < order+1; i++){
		free(A[i]);
	}
	free(A);
	free(X);
	free(B);
	free(F);
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
}



double f(double x){
	double val = 1/(1 + 25*pow(x,2));
	return val;
}



void interpolate(double* F, double* X, double xreq, double xstart, double xend, int order){

	if(xreq < xstart){
		printf("given x must lie between -1 and 1 \n");
	}
	else{
		int r;
		for(int i=0; i < order+1; i++){
			if(xreq > X[i]){
				r = i;									// Notes the interval that xreq is present in
			}
		}
		if(r == order){
			printf("given x must lie between -1 and 1 \n");
		}
		else{
			double val = F[r]*pow(X[r+1]-xreq,3)/(6*(X[r+1]-X[r])) + F[r+1]*pow(xreq-X[r],3)/(6*(X[r+1]-X[r])) + 
						(f(X[r])/(X[r+1]-X[r]) - F[r]*(X[r+1]-X[r])/6) * (X[r+1]-xreq) + 
						(f(X[r+1])/(X[r+1]-X[r]) - F[r+1]*(X[r+1]-X[r])/6) * (xreq-X[r]);
			printf("%lf \n", val);
		}
	}
}