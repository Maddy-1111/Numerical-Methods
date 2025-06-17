/***********************************************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 27/10/2023
Inputs		: Number of sample points(N), Standard deviation of noise(sigma_n)
Outputs		: sigma_n, A, sigma_g, R^2
Description : This code creates a data set of a lorentzian function and adds noise to it
			  It then sends the data to gnuplot and fits it to a gaussian function.
			  It then prints out the goodness of fit and the gaussian characteristics to terminal.

***********************************************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>



double randn(double random);
double f(double x);												// lorentzian function as given in Moodle


int main(int argc, char*argv[]) {
	srand((int) time(NULL));
	int N = atoi(argv[1]);
	double sn = atof(argv[2]);									// sn is sigma_n

	double xstart = -2;
	double xend = 2;
	double* X = malloc((N)*sizeof(double));
	double* Y = malloc((N)*sizeof(double));

	for(int i=0; i < N; i++){									// Creating the array of sample points
		X[i] = xstart + ((double)i/(N-1))*(xend - xstart);
	}

	FILE* fptr = fopen("noisyfits.txt", "w");

	for(int i=0; i < N; i++){
		double noise = rand()/(double)(RAND_MAX);
		noise = sn*randn(noise);
		Y[i] = f(X[i]) + noise;
		fprintf(fptr, "%lf %lf\n", X[i], Y[i]);					// Writing the lorentzian data to a file
	}

	fflush(fptr);

	FILE* gnuptr = popen("gnuplot", "w");
	fprintf(gnuptr, 
		"set fit quiet\n"\
		"set fit logfile '/dev/null'\n"\
		"m(x) = mean\n"\
		"fit m(x) 'noisyfits.txt' u 1:2 via mean\n"\
		"SST = FIT_WSSR/(FIT_NDF+1)\n"\
		"f(x) = A * exp(-(x**2) / (2*(sg**2)))\n"\
		"fit f(x) 'noisyfits.txt' u 1:2 via A, sg\n"\
		"SSE = FIT_WSSR/(FIT_NDF+2)\n"\
		"R2 = (SST - SSE)/SST\n"\
		"print %lf,A,sg,R2\n", sn);


	fclose(gnuptr);
	fclose(fptr);
	return 0;
}



double randn(double random) {								// Takes in a uniformly random variable from -1 to 1 
	double temp = rand()/(double)(RAND_MAX);				// and converts it to a normal random variable with sigma = 1
	random = sqrt(-2*log(random))*sin(2*M_PI*(temp));
	return random;
}



double f(double x){
	double val = 1/(1 + 25*pow(x,2));
	return val;
}