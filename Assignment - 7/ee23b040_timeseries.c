/***********************************************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 04/10/2023
Inputs		: Number of signals - M, Time of each signal - T, Width of each signal - a
			  and Gaussian/Lorentzian (optional)
Outputs		: Tavg, aavg, Tstd, astd
Description : This program creates an array of data points which correspont to amplitude of signals over time.
			  A cernatin amount of normal noise is added to this data while storing it.
			  It then smoothens this noise by using a window average filter and calculates the time and width 
			  for each of the M peaks generated and stores it in arrays.

			  ** This code will work optimally for T/a ratios from 5 to 100 **

***********************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<time.h>

#define DIV (5*(T/a))

void lorentz(int M, double T, double a, double* data);
void gauss(int M, double T, double a, double* data);
void randn(double* rand1, double*rand2);
void smooth(double* data, int len);

int main(int argc, char*argv[]) {
	srand((int) time(NULL));
	int M = atoi(argv[1]);
	double T = atof(argv[2]);
	double a = atof(argv[3]);
	int set = 0;
	double tick = T/DIV;

	double* data = malloc(M*DIV*sizeof(double));

	if(argc < 5){
		lorentz(M, T, a, data);
		set++;
	}
	else if(argv[4][0] == 'l' || argv[4][0] == 'L'){
		lorentz(M, T, a, data);
		set++;
	}
	else{
		gauss(M, T, a, data);
	}

	smooth(data, M*DIV);

/*	
	FILE* fptr = fopen("signal.txt","w");
	for(int i=0; i < M*DIV; i++){
		fprintf(fptr, "%d, %f \n", i, data[i]);
	}

	fclose(fptr);
*/

	double* T_temp = malloc(M*sizeof(double));
	double* a_val = malloc(M*sizeof(double));
	double* T_val = malloc((M-1)*sizeof(double));
	double Tavg, aavg, Tstd, astd;

	if(set == 1){
		for(int m=0; m < M; m++){

			int i = 0;
			while(data[i+(int)(m*DIV)] < 0.5)
				i++;

			double t1 = tick*(i+m*DIV);

			while(data[i+(int)(m*DIV)] > 0.5)
				i++;
			double t2 = tick*(i+m*DIV);

			a_val[m] = (t2-t1)/2;
			T_temp[m] = t2;
		}
	}
	else{
		for(int m=0; m < M; m++){

			int i = 0;
			while(data[i+(int)(m*DIV)] < 0.5)
				i++;

			double t1 = tick*(i+m*DIV);

			while(data[i+(int)(m*DIV)] > 0.5)
				i++;
			double t2 = tick*(i+m*DIV);

			a_val[m] = (t2-t1)/(2*sqrt(log(4)));
			T_temp[m] = t2;
		}
	}


	for(int i=0; i < M-1; i++){
		T_val[i] = T_temp[i+1] - T_temp[i];
		Tavg += T_val[i];
		aavg += a_val[i];
		Tstd += pow(T_val[i],2);
		astd += pow(a_val[i],2);
	}
	Tavg = Tavg/(M-1);
	aavg = (aavg+a_val[M-1])/M;
	Tstd = Tstd/(M-1) - pow(Tavg,2);
	astd = (astd+pow(a_val[M-1],2))/M - pow(aavg,2);

	printf("%f %f %f %f", Tavg, aavg, Tstd, astd);

	return 0;
}



void randn(double* rand1, double*rand2) {
	double temp;
	temp = sqrt(-2*log(*rand1))*cos(2*M_PI*(*rand2));
	*rand1 = sqrt(-2*log(*rand2))*sin(2*M_PI*(*rand1));
	*rand2 = temp;
}



void smooth(double* data, int len) {
	int span = 6;

	for(int i = span/2; i < len-span/2; i++){
		double temp = 0;

		for(int j=0; j < span; j++){
			temp += data[i-(span/2)+j];
		}

		data[i] = temp/span;
	}
}



void lorentz(int M, double T, double a, double* data) {

	double t = 0;

	for(int m=0; m < M; m++){
		double Tz = rand()/(double)(RAND_MAX);
		double az = rand()/(double)(RAND_MAX);
		randn(&Tz, &az);

		Tz = T*Tz/60;
		az = a*(1 + az/60);

		for(int j=0; j < DIV; j++){

			double nz = rand()/(double)(RAND_MAX);
			double temp = rand()/(double)(RAND_MAX);
			randn(&nz, &temp);
			nz = nz/30;

			data[j+(int)(m*DIV)] = pow(az,2)/(pow(t-(m+0.5)*T-Tz,2)+pow(az,2)) + nz;
			t += T/DIV;
		}
	}
}



void gauss(int M, double T, double a, double* data) {

	double t = 0;

	for(int m=0; m < M; m++){
		double Tz = rand()/(double)(RAND_MAX);
		double az = rand()/(double)(RAND_MAX);
		randn(&Tz, &az);

		Tz = T*Tz/60;
		az = a*(1 + az/60);

		for(int j=0; j < DIV; j++){

			double nz = rand()/(double)(RAND_MAX);
			double temp = rand()/(double)(RAND_MAX);
			randn(&nz, &temp);
			nz = nz/30;

			data[j+(int)(m*DIV)] = exp((-pow(t-(m+0.5)*T-Tz,2))/(2*pow(az,2))) + nz;
			t += T/DIV;
		}
	}
}
