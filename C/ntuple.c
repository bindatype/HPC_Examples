#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 5

int main(void) {
	int span[] = {1,5,3,4,3};
	int sum = 0;
	double **m,*p;

	for ( int i = 0; i < ROWS; i++ )
		sum += span[i];

	m = malloc( sizeof(double) * ROWS);
	p = malloc( sizeof(double) * sum );

	sum = 0;
	for (int i = 0; i < ROWS; i++ ) {
		*(m+i) = p + sum ;
		sum +=span[i];
	}

	for (int i = 1; i < ROWS; i++ ) {
		printf("%d %d %d\n",*(m+i),*(m+i-1),*(m+i)-*(m+i-1));
	}

	for (int i = 0; i < sum; i++ ) {
		*(p+i) = i;
		printf("p[%d] = %f ",i,p[i]);
	}
	printf("\n");

	for (int i = 0; i < ROWS; i++ ) {
		for (int j = 0; j < span[i]; j++ ) {
			printf("%f ",m[i][j]);
		}
		printf("\n");
	}

	free(p);
	free(m);
	return 0;
}
