#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 20000

using namespace std;

double clk[100]={0.};

int main(){
	clk[0] = 1000*omp_get_wtime();

        double *x;
        double *y;
	x = (double *) malloc( SIZE * sizeof(double ) );
	y = (double *) malloc( SIZE * sizeof(double ) );


        double **a;
        a  = (double **) malloc( SIZE * sizeof(double *) );
        *a =  (double *) malloc( SIZE * SIZE * sizeof(double) );

        for ( int i = 0; i < SIZE; i++ ) 
          *( a+i ) = *a + i*SIZE; // (Eq. 2)
	
/*
 * double a[SIZE][SIZE]={{0.}};
	double x[SIZE]={0.};
	double y[SIZE]={0.};
*/	srand(time(NULL));	
 
clk[10] = 1000 * omp_get_wtime();
//#pragma omp parallel for
	for (int i=0; i < SIZE; i++) {
		x[i] = rand()/(double)RAND_MAX;
		y[i] = rand()/(double)RAND_MAX;

	}

clk[20] = 1000 * omp_get_wtime();
#pragma omp parallel for
	for (int i=0; i < SIZE; i++) {
//#pragma omp critical 
  		for (int j=0; j < SIZE; j++) {
//#pragma omp critical 
			a[i][j] = 3*a[i][j]*x[j]*y[i];
		}
	}

clk[30] = 1000 * omp_get_wtime();
//#pragma omp parallel for
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
	cout << " Allocations: "<< clk[10]-clk[0] << " [ms] (" <<100*(clk[10]-clk[0])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " Random: "<< clk[20]-clk[10] << " [ms] (" <<100*(clk[20]-clk[10])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " M(VV)r: "<< clk[30]-clk[20] << " [ms] (" <<100*(clk[30]-clk[20])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " V.Vr: "<< clk[40]-clk[30] << " [ms] (" <<100*(clk[40]-clk[30])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " MVw: "<< clk[50]-clk[40] << " [ms] (" <<100*(clk[50]-clk[40])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " Total: "<< clk[99]-clk[0] << " [ms]" <<endl;

  free(x);
  free(y);
  free(*a);
  free(a);
  return 0;
}
