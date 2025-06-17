/***********************************************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 14/11/2023
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
		"set xrange [-7:7]\n"
		"set yrange [-7:7]\n"
		"plot 'ee23b040_hemplot.dat' u 1:2 title 'Data points'\n");

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
	FILE* fptr = fopen("ee23b040_hemplot.dat", "w");

	for(int i=0; i < 750; i++){

		double r = r0*a/b;
		double theta = (2*M_PI*a) / b;

		double x = x0 + r*cos(theta);
		double y = y0 + r*sin(theta);

		if(theta > 0){
			fprintf(fptr, "%lf %lf\n", x, y);				// Appending the (x,y) values to a file
		}

		int buf = b;										// Updating to the next 2 fibonacci numbers
		b = a;
		a = buf;
		a = a+b;
	}

	fclose(fptr);
}