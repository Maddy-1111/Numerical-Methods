/***********************************************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 27/12/2023
Inputs		: No inputs taken
Outputs		: Creates a gnuplot graph of the Fibonacci spiral
Description : This program iteratively calculates the fibonacci sequence.
			  It calculates r and theta from two successive fibonacci numbers and then appends the corresponding
			  x,y values to a file.
			  This file is then plotted by calling gnuplot.

***********************************************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


#define ITER 15										// Number of terms taken in the spiral
#define INTER 10									// Number of interpolating points b/w successive fibonacci terms


int hem(int n);
void hemplot(double x0, double y0, double r0);


int main(int argc, char*argv[]) {
	double x0 = 0;
	double y0 = 0;
	double r0 = 1;

	hemplot(x0, y0, r0);

	FILE* gnuptr = popen("gnuplot -persist", "w");				// Plotting the (x,y) values stored
	fprintf(gnuptr, 
		"set title 'Fibonacci spiral'\n"
		"plot 'ee23b040_hemplot_corrected.dat' u 1:2 w lines title 'Data points'\n");

	fclose(gnuptr);
	return 0;
}



int hem(int n){											// Function to recursively calculate the nth fibonacci number
	if(n == 1){
		return 0;
	}
	if(n == 2){
		return 1;
	}
	else{
		return (hem(n-1) + hem(n-2));
	}
}



void hemplot(double x0, double y0, double r0){
	int a = 2;
	int b = 1;
	double r = r0;
	double theta = 0;

	FILE* fptr = fopen("ee23b040_hemplot_corrected.dat", "w");

	for(int i=0; i < ITER; i++){

		double r_old = r;
		double theta_old = theta;

		r = r*a/(double)b;
		theta += M_PI*a / (double)(b*2);

// This for loop exists only because we need to interpolate 'r' and 'theta' to get a smooth graph
		for(int j=0; j < INTER; j++){
			double k = (double)j/INTER;

			double R = r_old*(1-k) + r*k;
			double angle = theta_old*(1-k) + theta*k;
			double x = x0 + R*cos(angle);
			double y = y0 + R*sin(angle);

			fprintf(fptr, "%lf %lf\n", x, y);				// Appending the (x,y) values to a file
		}

		int buf = b;										// Updating to the next 2 fibonacci numbers
		b = a;
		a = buf;
		a = a+b;
	}

	fclose(fptr);
}