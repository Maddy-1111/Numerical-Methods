/***********************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 08/09/2023
Description : This takes in parameters from the user and generates a txt file with 
			  the points required to construct a logistic map.
Inputs		: Takes in 3 terminal arguments (max iterations, step size of "r" and tolerance)
Outputs		: Creates a txt file called "outfile.txt" which contains columns
			  (value of "r", value of "x")

***********************************************************************************/


#include<stdio.h>
#include<stdlib.h>


double f(double x, double r);							   // relation b/w x(i+1) and x(i) 

int main(int argc, char* argv[]) {
	
	double max_iter = atof(argv[1]);
	double r_step = atof(argv[2]);
	double err = atof(argv[3]);
	double r = 0;
	double val;

	FILE* fptr = fopen("outfile.txt", "w");

	while(r < 4 && r >= 0){

		val = 0.502;										// starting value of x (x0).

		for (int count = 0; count < max_iter; count++){
			val = f(val, r);
			if (count > max_iter*0.5){						
				fprintf(fptr, "%f %f \n", r, val);
			}
		}

		r = r + r_step;
	}

	fclose(fptr);
	return 0;
}


double f(double x, double r){
	return r*x*(1-x);
}
