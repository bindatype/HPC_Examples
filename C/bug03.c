#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

	double *a, *b;
	a = malloc(10*sizeof(double));
	b = malloc(10*sizeof(double));

        for( int i = 0; i < 10; i++) {
		a[i] = (double) i;
		b[i] = (double) i;
	} 

     /* Old code for reference ... leave commented out!!! */ 
        for( int i = 0; i < 20; i++) {
                a[i] = (double) i;
        }

        for( int i = 1; i < 10; i++) {
		printf("%f %f\n",a[i],b[i]);
	}

	free(a);
	free(b);
  	return 0;
}
