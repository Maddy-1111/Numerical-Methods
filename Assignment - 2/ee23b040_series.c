/*
	RollNo,Name : EE23B040,Madhav T
	Date 		: 18/8/2023
	Version		: 1
	Description : This program calculates the value of sin(x) using taylor expansion
				  upto a certain accuracy
	Inputs 		: Takes in 2 inputs, 
				  First input is the number of terms in the expansion to be evaluated
				  Second input is the value of whose sin will be calculated
	Outputs 	: Gives 2 outputs
				  First output is the approximate sin value calculated
				  Second output is the error from the actual sin value
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float mysin(int n, float x); //Calculates sin("x") using taylor expansion upto "n" terms

unsigned long factorial(int n); //Calculates the factorial of a given number "n"



int main (int argc, char*argv[]) {
	int n = atoi(argv[1]);
	float x = atof(argv[2]);
	float error = sin(x) - mysin(n,x);
	printf("%0.3f,%0.3f", mysin(n,x), error);
	return 0;
}



float mysin(int n, float x) {
	float val = 0;
	for (int i=1; i<=n; i++){
		val += pow(-1,i+1)*pow(x,2*i-1)/factorial(2*i-1);
	}
	return val;
}



unsigned long factorial(int n) {
	unsigned long fact = 1;
	for (int i=1; i<=n; i++){
		fact = fact*i;
	}
	return fact;
}