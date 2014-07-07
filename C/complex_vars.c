#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

/*
 * Algorithm to find the cube roots, including complex values, using the cubic formula. 
 * Adapted from Abramowitz and Stegun: Handbook of Mathematical Functions, pg. 17. 
 *
 * Function accepts 3 doubles, a2, a1, and a0 
 * Returns 6 doubles (Re and Im values for z1, z2, and z3) 
 *
 * This code also illustrates the use of complex values in GCC.
 *
 */  

int main (int argc, char **argv){

	//-- Given a cubic equation of the form
	//      z^3 + a2*z^2 + a1*z + a0 = 0

	double a2,a1,a0;
	_Complex double temp1,temp2;

	/* Argument checking ... must have three integers, a2, a1, & a0 -- thus argc must equal 4 */

	switch(argc){
		case 4:
			a2 = atof(argv[1]);
			a1 = atof(argv[2]);
			a0 = atof(argv[3]);
			break;
		default:
			printf("Usage: ./cuberoot a2 a1 a0\n");
			exit(11);
	}

	//print coefficients
	printf("a2= %e\ta1= %e\ta0= %e\n",a2,a1,a0);

	//-- Calculate Q and R.
	_Complex double Q,R;
	Q = a1/3 - a2*a2/9;
	R = (a1*a2 - 3*a0)/6.- a2*a2*a2/27.; 

	printf("Q: %e\n",creal(Q));
	printf("R: %e\n",creal(R));
	printf("Q^3: %e\n",creal(Q*Q*Q));
	printf("R^2: %e\n",creal(R*R));

	printf("Q^3+R^2: %e\n",creal(Q*Q*Q+R*R));

	//-- Calculate s1 and s2
	_Complex double s1, s2;

	temp1 = R + csqrt( Q*Q*Q+R*R );
	temp2 = R - csqrt( Q*Q*Q+R*R );	

	if (creal(temp1) < 0.) {
		s1 = -cpow(-temp1,1./3. );
	}
	else{
		s1 = cpow(temp1,1./3. );
	}
	if ( creal(temp2) < 0 ) {
		s2 = -cpow(-temp2,1./3. );
	}
	else{
		s2 = cpow(temp2,1./3. );
	}

	printf("Re csqrt( Q*Q*Q+R*R ) %e\n",creal(csqrt( Q*Q*Q+R*R )));
	printf("Im csqrt( Q*Q*Q+R*R ) %e\n",cimag(csqrt( Q*Q*Q+R*R )));
	printf("s1: %e + %e I\n",creal(s1),cimag(s1));
	printf("s2: %e + %e I\n",creal(s2),cimag(s2));



	//-- Compute roots
	_Complex double z1, z2, z3;
	z1 = -a2/3. + (s1 + s2);
	z2 = -a2/3. - (s1 + s2)/2. + I*sqrt(3.)*(s1 - s2)/2.;
	z3 = -a2/3. - (s1 + s2)/2. - I*sqrt(3.)*(s1 - s2)/2.;

	//-- Print results to STDOUT
	printf("root 1: ( %e + %e I ) \n",creal(z1), cimag(z1));
	printf("root 2: ( %e + %e I ) \n",creal(z2), cimag(z2));
	printf("root 3: ( %e + %e I ) \n",creal(z3), cimag(z3));
	printf("-----------------------------------------------\n");
	printf("a2: %e + %e \n",-1*creal(z1+z2+z3),-1*cimag(z1+z2+z3) );
	printf("a1: %e + %e \n",creal(z1*z2 + z2*z3 + z1*z3),cimag(z1*z2 + z2*z3 + z1*z3) );
	printf("a0: %e + %e \n",-1*creal(z1*z2*z3),-1*cimag(z1*z2*z3) );


	return 0;
}
