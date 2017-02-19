#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 10000

using namespace std;

double clk[100]={0.};

int main(){


	clk[0] = 1000*omp_get_wtime();

	double a[SIZE][SIZE]={{0.}};
	double b[SIZE][SIZE]={{0.}};
	double x[SIZE]={0.};
	double y[SIZE]={0.};
	srand(time(NULL));	

clk[10] = 1000 * omp_get_wtime();
#pragma omp parallel for
	for (int i=0; i < SIZE; i++) {
		x[i] = rand()/(double)RAND_MAX;
		y[i] = rand()/(double)RAND_MAX;
	}

clk[20] = 1000 * omp_get_wtime();
#pragma omp parallel for
	for (int i=0; i < SIZE; i++) {
  		for (int j=0; j < SIZE; j++) {
			a[i][j] = x[i]*y[j];
			b[i][j] = x[j]*y[i];
		}
	}

clk[30] = 1000 * omp_get_wtime();
#pragma omp parallel for
	for (int i=0; i < SIZE; i++) {
		y[i] = 	x[i]*y[i];
	}

clk[40] = 1000 * omp_get_wtime();
#pragma omp parallel for
	for (int i=0; i < SIZE; i++) {
	  for (int j=0; j < SIZE; j++) {
		y[i] = 	a[i][j]*x[j];
	  }
	} 

clk[50] = 1000 * omp_get_wtime();

  	cout << y[32] << endl;
	clk[99] = 1000*omp_get_wtime();
	cout << " 10,0: "<< clk[10]-clk[0] << " [ms] (" <<100*(clk[10]-clk[0])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " 20,10: "<< clk[20]-clk[10] << " [ms] (" <<100*(clk[20]-clk[10])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " 30,20: "<< clk[30]-clk[20] << " [ms] (" <<100*(clk[30]-clk[20])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " 40,30: "<< clk[40]-clk[30] << " [ms] (" <<100*(clk[40]-clk[30])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " 50,40: "<< clk[50]-clk[40] << " [ms] (" <<100*(clk[50]-clk[40])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " Total: "<< clk[99]-clk[0] << " [ms]" <<endl;
  return 0;
}
