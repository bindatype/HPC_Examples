/*
   Illustrate the equivalent notations:
   (1)	a[i][j] = *(*(a+i)+j)
   (2)		= *(a+i*COLS+j)
   (3)	   x[i] = *(x+i)
   */


#include <stdio.h>
#include <stdlib.h>

#ifndef _SIZE
#define _SIZE 3
#endif
void square(double *in) {
	*in = (*in)*(*in);
}

int main (void) {

	int i,j,k;
	double ***m;
	m  = malloc( _SIZE * sizeof(double **) );
	*m  = malloc( _SIZE * _SIZE * sizeof(double *) );
	**m = malloc( _SIZE * _SIZE * _SIZE * sizeof(double) );

	for ( i = 0; i < _SIZE; i++ ) {
		*(m+i)  = *m + i * _SIZE;
		for ( j = 0; j < _SIZE; j++ ) { 
			*(*(m+i)+j) = *(*m + i * _SIZE) + j*_SIZE;
			for ( k = 0; k < _SIZE; k++ ) { 
				m[i][j][k] = i+j+k;
			}
		}
	}
	for ( i = 0; i < _SIZE; i++ ) {
		for ( j = 0; j < _SIZE; j++ ) {
			for ( k = 0; k < _SIZE; k++ ) {
				printf("[%d][%d][%d]: \n",m[i][j][k]);
			}
		}
	}


	free(*m);
	free(m);

	return 0;
}
