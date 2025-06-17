/***********************************************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 04/10/2023
Inputs		: Number of signals - M, Time of each signal - T, Width of each signal - a
			  and Gaussian/Lorentzian (optional)
Outputs		: Tavg, aavg, Tstd, astd
Description : This program creates a file("signal.txt") of data points which corresponds to the 
			  amplitude of signals over time.
			  A cernatin amount of normal noise is added to this data while storing it.
			  It then reads through the file, uses an exponential filter as it goes and stores the
			  values of "a" and "T" on spot.
			  At the end of the file, it calculates Tavg, aavg, Tstd, astd and prints it.

			  ** This code will work optimally for T/a ratios from 5 to 100(or more) **

***********************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<time.h>

#define DIV (5*(T/a))

struct peakinfo {										// A struct to store info of each peak
	double a;
	double T;
};

void lorentz(int M, double T, double a);
void gauss(int M, double T, double a);
void randn(double* rand1, double* rand2);				// Box-muller transform to create a normal distribution

int main(int argc, char*argv[]) {
	srand((int) time(NULL));

	int M = atoi(argv[1]);
	double T = atof(argv[2]);
	double a = atof(argv[3]);
	int set = 0;
	double tick = T/DIV;

	struct peakinfo* peaks = malloc(M*sizeof(struct peakinfo));		// Array to store the structs

	if(argc < 5){
		lorentz(M, T, a);
		set++;
	}
	else if(argv[4][0] == 'l' || argv[4][0] == 'L'){
		lorentz(M, T, a);
		set++;
	}
	else{
		gauss(M, T, a);
	}


	double Tdel, Tavg, aavg, Tstd, astd;
	double t1, t2, amp_cur, amp_prev = 0;
	double k = 0.5;													// k value used in the exponential filter
	FILE* fptr = fopen("signal.txt", "r");


	for(int m=0; m < M; m++){

		do{
			fscanf(fptr, "%lf %lf", &t1, &amp_cur);					// Reads the file till amplitude of the point
			amp_cur = k*amp_prev + (1-k)*amp_cur;					// equals 0.5, then temporarily stores the
			amp_prev = amp_cur;										// time at which this occured
		} while(amp_cur < 0.5);

		do{
			fscanf(fptr, "%lf %lf", &t2, &amp_cur);					// Similar to prev do-while loop
			amp_cur = k*amp_prev + (1-k)*amp_cur;
			amp_prev = amp_cur;
		} while(amp_cur > 0.5);


		if(set == 1){
			peaks[m].a = (t2-t1)/(2*sqrt(log(4)));
		}
		else{
			peaks[m].a = (t2-t1)/2;
		}
		peaks[m].T = t2;
	}


	for(int i=0; i < M-1; i++){

		Tdel = peaks[i+1].T - peaks[i].T;							// delT corresponds to time difference
		Tavg += Tdel;												// between successive peaks
		aavg += peaks[i].a;
		Tstd += pow(Tdel,2);
		astd += pow(peaks[i].a,2);

	}
	Tavg = Tavg/(M-1);
	aavg = (aavg+peaks[M-1].a)/M;
	Tstd = Tstd/(M-1) - pow(Tavg,2);
	astd = (astd+pow(peaks[M-1].a,2))/M - pow(aavg,2);

	printf("%lf %lf %lf %lf\n", Tavg, aavg, Tstd, astd);

	fclose(fptr);
	return 0;
}



void randn(double* rand1, double*rand2) {
	double temp;
	temp = sqrt(-2*log(*rand1))*cos(2*M_PI*(*rand2));					// Box muller formula
	*rand1 = sqrt(-2*log(*rand2))*sin(2*M_PI*(*rand1));
	*rand2 = temp;
}



void lorentz(int M, double T, double a) {

	FILE* fptr = fopen("signal.txt","w");
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
			nz = nz/30;													// Background noise

			double buf = pow(az,2)/(pow(t-(m+0.5)*T-Tz,2)+pow(az,2)) + nz;
			fprintf(fptr, "%lf %lf\n", t, buf);
			t += T/DIV;
		}
	}
	fclose(fptr);	
}



void gauss(int M, double T, double a) {

	FILE* fptr = fopen("signal.txt","w");
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

			double buf = exp((-pow(t-(m+0.5)*T-Tz,2))/(2*pow(az,2))) + nz;
			fprintf(fptr, "%lf %lf\n", t, buf);
			t += T/DIV;
		}
	}
	fclose(fptr);
}