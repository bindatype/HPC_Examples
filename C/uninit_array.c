#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000


int main()
{
	double *array;
	array = (double *) malloc(sizeof (double) * SIZE );

	for ( int i = 0; i < SIZE; i++ )
		printf("%f\n",*(array+i) );

	return 0;
}
