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

	int i,j;
	double **m;
	m  = malloc( _SIZE * sizeof(double *) );
	*m = malloc( _SIZE * _SIZE * sizeof(double) );

	for ( i = 0; i < _SIZE; i++ ) 
		*( m+i ) = *m + i*_SIZE; // (Eq. 2)

	for ( i = 0; i < _SIZE; i++ ) 
		for ( j = 0; j < _SIZE; j++ ) 
			*( *(m+i) + j ) = i+j;

	for ( i = 0; i < _SIZE; i++ ) {
		for ( j = 0; j < _SIZE; j++ ) { 
			//-- Two lines are synonyms. 
			//		square(  &m[i][j]  );
			square(  *(m+i)+j  );
			printf("%f ",m[i][j]);
		}
		printf("\n");
	}

	free(*m);
	free(m);

	return 0;
}
