#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

	int i;
     
	double *a, *b;
	a = malloc(10*sizeof(double));
	b = malloc(10*sizeof(double));

        for( i = 0; i < 10; i++) {
		a[i] = (double) i;
		b[i] = (double) i;
	} 

        for( i = 0; i <=10; i++) {
		printf("%f %f\n",a[i],b[i]);
	}
	free(a);
	free(a);

  	return 0;
}
