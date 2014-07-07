#include <stdio.h>
#include <stdlib.h>

/* Program for creating logistic map data. */

int main(int argc, char **argv){
	/* i and j are loop counters...i=>x index, j=>r index.
	 * x is the recursive variable
	 * r is the scaling factor
	 */
	int i,j;
	double r,x,upperBound,lowerBound;
	x=0.00079; 	/* Initialize variables */
	lowerBound=r=2.5; /* Upper and lower bounds on r */
	upperBound=4.0;

	FILE *f; 	/* Open file for writing */
	f=fopen("results.dat","w"); 

	for (j=0 ; j<1000 ; j++){ /* r ranges from 2.5 to 4 through 1000 steps. */
		r+=(upperBound-lowerBound)/1000;

		for (i=0 ; i<1000 ; i++){ /* calculate 1000 x's for each value of r. */
			x=r*x*(1-x);

			if(i>=900){  /* keep only the last 100 x's for each value of r and write r,x pairs to file. */
				fprintf(f,"%e %e\n",r,x);
			}

			if ( x < 0 || x > 1 ){ /* Do sanity checking. If x strays outside 0,0 1,0 1,1 0,1 square exit with error */
				fprintf( stderr, "x outside bounds. Force quit on x=%e, i= %u, j=%u\n",x,i,j);
				return 1; 
			}


		}
	}

	fclose(f); /* Done with file so clean up. */

	return 0;
}

