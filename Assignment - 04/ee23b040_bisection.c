/***********************************************************************************

RollNo,Name : EE23B040,Madhav T
Date 		: 01/09/2023
Description : Estimates the root of a specific function upto a certain degree
			  using two methods
			  If "1" is the input, the program uses bisection method and prints
			  					   the calculated root
			  If "2" is the input, the program uses false positive method and prints
			  					   the calculated root

***********************************************************************************/

#include<stdio.h>
#include<math.h>
#include<string.h>


double f(double x);  // This is the 5th dergee polynomial given in moodle
void bisection();
void false_position();


int main(int argc, char*argv[]) {

	if (strcmp(argv[1],"1") == 0) {
		bisection();
	}

	if (strcmp(argv[1],"2") == 0) {
		false_position();
	}

	return 0;
}



double f(double x) {
	double y = -25 + 82*x - 90*pow(x,2) + 44*pow(x,3) - 8*pow(x,4) + 0.7*pow(x,5);
	return y;
}



void bisection() {

	double err = 1;
	double epsilon = 0.1;
	double xl = 0.5;
	double xu = 1;
	double xn;

	while(err > epsilon) {

		xn = (xl + xu)/2;
		err = fabs((xn-xl)/xn);

		if (f(xn)*f(xl) < 0) {
			xu = xn;
		}
		else if (f(xn)*f(xu) < 0) {
			xl = xn;
		}

	}

	printf("%f", xn);
}



void false_position() {

	double err = 1;
	double epsilon = 0.002;
	double xl = 0.5;
	double xu = 1;
	double xn;

	while (err > epsilon) {

		xn = xl - (xu-xl)*f(xl)/(f(xu)-f(xl));
		err = fabs((xn-xl)/xn);

		if (f(xn)*f(xl) < 0) {
			xu = xn;
		}
		else if (f(xn)*f(xu) < 0) {
			xl = xn;
		}

	}

	printf("%f", xn);
}