/***********************************************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 20/10/2023
Inputs		: Order of approximation, starting point, ending point, x value to be found
Outputs		: Value of x which was required
Description : This program uses the Lagrange and Newton interpolation methods to fit a curve onto a given 
			  set of points, then caluclate the value of this curve at a required x.
			  This program samples points which are equidistant from each other (the algorithm will still
			  work if the points are not equidistant)

***********************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


double f(double x);													// function as given in Moodle
double lagrange(double* X, double* Y, int order, double xreq);
double newton(double* X, double* Y, int order, double xreq);

int main(int argc, char*argv[]) {
	int order = atoi(argv[1]);
	double xstart = atof(argv[2]);
	double xend = atof(argv[3]);
	double xreq = atof(argv[4]);

	double* X = malloc((order+1)*sizeof(double));
	double* Y = malloc((order+1)*sizeof(double));

	for(int i=0; i < order+1; i++){									// Creating the array of sample points
		X[i] = xstart + ((double)i/(order))*(xend - xstart);
		Y[i] = f(X[i]);
	}

	double* Xnew = malloc((order+1)*sizeof(double));
	double* Ynew = malloc((order+1)*sizeof(double));
	double del = 0.2;

	for(int i=0; i < order+1; i++){
		Xnew[i] = X[i] + del;
		Ynew[i] = lagrange(X, Y, order, Xnew[i]);
	}

	printf("%lf\n", newton(Xnew, Ynew, order, xreq));
	return 0;
}



double f(double x){
	double val = 1/(1 + 25*pow(x,2));
	return val;
}


double lagrange(double* X, double* Y, int order, double xreq){
	double ans = 0;

	for(int i=0; i < order+1; i++){
		double term = Y[i];
		for(int j=0; j < order+1; j++){
			if(i != j){
				term = term*(xreq-X[j])/(X[i]-X[j]);			// Creating the terms in Lagrang's formula
			}
		}
		ans += term;
	}

	return ans;
}


double newton(double* X, double* Y, int order, double xreq){
	double** matrix = malloc((order+1)*sizeof(double*));
	for(int i=0; i < order+1; i++){
		matrix[i] = malloc((order+1)*sizeof(double));			// Creating a 2D array
	}

	for(int i=0; i < order+1; i++){
		matrix[i][0] = Y[i];
	}

// Filling the matrix with 1st, 2nd ... nth "derevatives".
	for(int j=1; j < order+1; j++){
		for(int i=0; i < order+1-j; i++){
			matrix[i][j] = (matrix[i+1][j-1] - matrix[i][j-1])/(X[i+j] - X[i]);
		}
	}

	double term = 1;
	double ans = matrix[0][0];

	for(int k=1; k < order+1; k++){
		term = term*(xreq-X[k-1]);
		ans = ans + term*matrix[0][k];						// Summing the terms in Newton's formula
	}

	return ans;
}