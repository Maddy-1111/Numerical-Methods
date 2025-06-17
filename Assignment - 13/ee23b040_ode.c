/***********************************************************************************************************

RollNo, Name: EE23B040, Madhav T
Date 		: 3/11/2023
Inputs		: Initial angle(theta_start), Final angle(theta_stop), Loss factor(alpha), Increment(delta_t)
Outputs		: alpha, delta_t, R^2_Euler, R^2_Heun
Description : This program calculates the trajectory of a magnet in a fixed magnetic field by numerically
			  solving a set of differential equations. It does this by 3 methods (euler, heun and rk45).
			  It writes the co-ordinates of theta and phi of the magnet for different time values in 3
			  seperate files named "euler_data.txt", "heun_data.txt", "rk45_data.txt".
			  It then takes these values and compares the goodness of fit of euler and heun against rk45.

			  ** The values of increment taken as input are truncated to the 2nd decimal place **

***********************************************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#define gamma 1.76e11
#define H 2e-11
#define Hk 0
#define gold_delta_t 0.01


double diff_theta(double theta, double alpha);									// differential equation for theta
double diff_phi(double theta, double d_theta, double alpha);					// differential equation for phi
void euler(double theta_start, double theta_stop, double alpha, double delta_t);
void heun(double theta_start, double theta_stop, double alpha, double delta_t);
void rk45(double theta_start, double theta_stop, double alpha, double delta_t);
double R2calc(char* fpath_dat, char* fpath_acc, double factor);

int main(int argc, char*argv[]) {

	double theta_start = atof(argv[1]);
	double theta_stop = atof(argv[2]);
	double alpha = atof(argv[3]);
	double delta_t = atof(argv[4]);

	double factor = delta_t / gold_delta_t;
	delta_t = floor(delta_t / gold_delta_t) * gold_delta_t;				// Truncating the user's increment input

	// Solving the differential equations using different methods
	euler(theta_start, theta_stop, alpha, delta_t);
	heun(theta_start, theta_stop, alpha, delta_t);
	rk45(theta_start, theta_stop, alpha, gold_delta_t);					// Passed in the golden delta_t (not delta_t)

	// Calculating R2 values
	double R2_euler = R2calc("euler_data.txt", "rk45_data.txt", factor);
	double R2_heun = R2calc("heun_data.txt", "rk45_data.txt", factor);

	// Printing outputs
	printf("%lf %lf %lf %lf\n", alpha, delta_t, R2_euler, R2_heun);

	return 0;
}



double diff_theta(double theta, double alpha){
	double val = gamma * alpha * (H*sin(theta) - Hk*sin(theta)*cos(theta)) / (pow(alpha,2) + 1);
	return val;
}

double diff_phi(double theta, double d_theta, double alpha){
	double val = d_theta / (alpha*sin(theta));
	return val;
}



void euler(double theta_start, double theta_stop, double alpha, double delta_t){

	double theta = theta_start;
	double phi = 0;
	double time = 0;

	FILE* feuler = fopen("euler_data.txt", "w");

	while(theta < theta_stop){

		fprintf(feuler, "%lf %lf %lf\n", time, theta, phi);
		double d_theta = diff_theta(theta, alpha);
		double d_phi = diff_phi(theta, d_theta, alpha);

		theta += d_theta * delta_t;
		phi += d_phi * delta_t;
		time += delta_t;
	}

	fclose(feuler);
}



void heun(double theta_start, double theta_stop, double alpha, double delta_t){

	double theta = theta_start;
	double phi = 0;
	double time = 0;

	FILE* fheun = fopen("heun_data.txt", "w");

	while(theta < theta_stop){

		fprintf(fheun, "%lf %lf %lf\n", time, theta, phi);
		double d_theta_1 = diff_theta(theta, alpha);
		double d_theta_2 = diff_theta(theta + d_theta_1*delta_t, alpha);

		double d_phi_1 = diff_phi(theta, d_theta_1, alpha);
		double d_phi_2 = diff_phi(theta + d_theta_1*delta_t, d_theta_2, alpha);

		theta += (d_theta_1 + d_theta_2) * delta_t / 2;
		phi += (d_phi_1 + d_phi_2) * delta_t / 2;
		time += delta_t;
	}

	fclose(fheun);
}



void rk45(double theta_start, double theta_stop, double alpha, double delta_t){		// Runge Kutta 4th Order

	double theta = theta_start;
	double phi = 0;
	double time = 0;

	FILE* frk45 = fopen("rk45_data.txt", "w");

	while(theta < theta_stop){

		fprintf(frk45, "%lf %lf %lf\n", time, theta, phi);

		double d_theta_1 = diff_theta(theta, alpha);
		double d_theta_2 = diff_theta(theta + d_theta_1*delta_t/2, alpha);
		double d_theta_3 = diff_theta(theta + d_theta_2*delta_t/2, alpha);
		double d_theta_4 = diff_theta(theta + d_theta_3*delta_t, alpha);

		double d_phi_1 = diff_phi(theta, d_theta_1, alpha);
		double d_phi_2 = diff_phi(theta + d_theta_1*delta_t/2, d_theta_2, alpha);
		double d_phi_3 = diff_phi(theta + d_theta_2*delta_t/2, d_theta_3, alpha);
		double d_phi_4 = diff_phi(theta + d_theta_3*delta_t, d_theta_4, alpha);

		theta += (d_theta_1 + 2*d_theta_2 + 2*d_theta_3 + d_theta_4) * delta_t / 6;
		phi += (d_phi_1 + 2*d_phi_2 + 2*d_phi_3 + d_phi_4) * delta_t / 6;
		time += delta_t;
	}

	fclose(frk45);
}



double R2calc(char* fpath_dat, char* fpath_acc, double factor){			// Calculates the goodness of fit b/w two curves

	FILE* fdat = fopen(fpath_dat, "r");
	FILE* facc = fopen(fpath_acc, "r");

	double theta_avg = 0;
	double theta_dat, theta_acc;
	double count = 0;
	double SSR, SST;

	while(fscanf(fdat, "%*f %lf %*f", &theta_dat) != EOF){
		count += 1;
		theta_avg += theta_dat;
	}
	theta_avg = theta_avg / count;
	rewind(fdat);

	while(fscanf(fdat, "%*f %lf %*f", &theta_dat) != EOF && fscanf(facc, "%*f %lf %*f", &theta_acc) != EOF){

		SST += pow(theta_dat - theta_avg, 2);
		SSR += pow(theta_dat - theta_acc, 2);

		for(int i=0; i < factor-1; i++){
			fscanf(facc, "%*f %lf %*f", &theta_acc);
		}
	}

	double R2value = 1 - SSR/SST;

	fclose(fdat);
	fclose(facc);

	return R2value;
}