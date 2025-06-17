/***********************************************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 14/11/2023
Inputs		: 1 argv input - N (the number corresponding to the term of the required Fibonacci number)
Outputs		: Prints the value of the Nth Fibonacci number
Description : The program does this by recursively calling the hem() function

***********************************************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


int hem(int n);									// Function to recursively calculate the nth fibonacci number


int main(int argc, char*argv[]) {
	int N = atoi(argv[1]);

	int val = hem(N);
	printf("%d", val);

	return 0;
}


int hem(int n){
	if(n == 1){									// Setting a base case to return
		return 0;
	}
	if(n == 2){
		return 1;
	}
	else{
		return (hem(n-1) + hem(n-2));
	}
}