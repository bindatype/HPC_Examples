#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 20000

using namespace std;

double clk[100]={0.};


/*
 * X is a string of zeros at the end. 
 * Get fortran version running...Ron?
 *
 *
 *
 */

void InitXY(double *x, double *y){
	srand(time(NULL));	
 
	for (int i=0; i < SIZE; i++) {
		x[i] = rand()/(double)RAND_MAX;
		y[i] = rand()/(double)RAND_MAX;
	}
}

void MVVwithReplace(double **a, double *x, double *y){
	for (int i=0; i < SIZE; i++) {
  		for (int j=0; j < SIZE; j++) {
			a[i][j] = 3*a[i][j]*x[j]*y[i];
		}
	}
}

void transpose(double **a, double **b){
        for (int i=0; i < SIZE; i++) {
                for (int j=0; j < SIZE; j++) {
                        b[i][j] =  a[i][j];;
                }
        } 
}

void VVwithReplace(double *x, double *y) {
	for (int i=0; i < SIZE; i++) {
		y[i] = 	x[i]*y[i];
	}
}

void MV(double **a, double *x, double *y){
	for (int i=0; i < SIZE; i++) {
		for (int j=0; j < SIZE; j++) {
			y[i] = 	a[i][j]*x[j];
	  	}
	} 
}

int main(){
clk[0] = 1000*omp_get_wtime();

        double *x,*y;
	x = (double *) malloc( SIZE * sizeof(double ) );
	y = (double *) malloc( SIZE * sizeof(double ) );

        double **a,**b;
        a  = (double **) malloc( SIZE * sizeof(double *) );
        b  = (double **) malloc( SIZE * sizeof(double *) );
        *a =  (double *) malloc( SIZE * SIZE * sizeof(double) );
        *b =  (double *) malloc( SIZE * SIZE * sizeof(double) );

        for ( int i = 0; i < SIZE; i++ ){ 
          *( a+i ) = *a + i*SIZE; // (Eq. 2)
          *( b+i ) = *b + i*SIZE; // (Eq. 2)
	}
clk[10] = 1000 * omp_get_wtime();
  InitXY(x,y);

clk[20] = 1000 * omp_get_wtime();
  MVVwithReplace(a, x, y);
clk[30] = 1000 * omp_get_wtime();
  VVwithReplace(x,y);

clk[40] = 1000 * omp_get_wtime();
 MV(a,x,y);

clk[50] = 1000 * omp_get_wtime();
  transpose(a,b);

clk[60] = 1000 * omp_get_wtime();

  	cout << y[32] << endl;
	clk[99] = 1000*omp_get_wtime();
	cout << " Allocations: "<< clk[10]-clk[0] << " [ms] (" <<100*(clk[10]-clk[0])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " Random: "<< clk[20]-clk[10] << " [ms] (" <<100*(clk[20]-clk[10])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " M(VV)r: "<< clk[30]-clk[20] << " [ms] (" <<100*(clk[30]-clk[20])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " V.Vr: "<< clk[40]-clk[30] << " [ms] (" <<100*(clk[40]-clk[30])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " MVw: "<< clk[50]-clk[40] << " [ms] (" <<100*(clk[50]-clk[40])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " Trace "<< clk[60]-clk[50] << " [ms] (" <<100*(clk[60]-clk[50])/(clk[99]-clk[0]) <<"%)"<<endl;
	cout << " Total: "<< clk[99]-clk[0] << " [ms]" <<endl;

        for ( int j = 0; j < 10; j++ ){
	  cout << x[j] << " " << y[j] << endl;	
	} 

  free(x);
  free(y);
  free(*a);
  free(a);
  return 0;
}
