#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include "comp-phys.h"

#define PI 3.14159

/* Lengths in meters unless otherwise noted. */
/* Energies and Momenta in GeV unless otherwise noted. */

/* Main Body */
int main (int argc, char **argv){

	double x,y,r; // Box-Mueller variables

	srand(atoi(argv[1])* (unsigned)time(NULL));

	int i;
#pragma omp parallel private (i) 
	for (i=0;i <1000000;i++){
//	for (i=0;i <10000000;i++){

		/* Beam Quantities */
		double mean_beam_energy = 2.3; // In GeV
		double beam_energy;
		double beam_momentum[3];
		double beam_resolution = 0.05;

		/* Target Quantities */
		double target_length = 0.15;
		double target_position;
		double length;
		double target_vec[3];

		/* Scattering Quantities */
		double theta,theta_central = 0.4014,phi;
		double theta_left,theta_right,phi_top,phi_bottom;
		double KE;

		/* Detector Corners */
		double lt[3]={-0.5,0.5,10.},
		       rt[3]={0.5,0.5,10.},
		       lb[3]={-0.5,-0.5,10.},
		       rb[3]={0.5,-0.5,10.};

		/* Unit vectors */
		double ihat[3]={1,0,0};
		double jhat[3]={0,1,0};
		double khat[3]={0,0,1};

		/* Set intial beam energy. 
		 * Smear energy with gaussian using box-mueller. */
		x = ( (double)rand())/( (double)RAND_MAX);
		y = ( (double)rand())/( (double)RAND_MAX);
		r = x*x+y*y;
		beam_energy = mean_beam_energy + 
			beam_resolution * sqrt( -2.*log(x) )*cos(2*PI*y);


		/* Choose a scattering point inside target. */
		length = ( (double)rand())/( (double)RAND_MAX);
		target_position = 
			-log( 1 - ( 1-exp(target_length) ) * length ) 
			+target_length/2.  ;

		/* Determine scattering point in detector frame */
		target_vec[0] = -1. * cos( theta_central ) 
			* target_position;
		target_vec[1] = 0.;
		target_vec[2] = sin( theta_central ) * target_position;

		/* Determine theta_left theta_right. */
		double flight[3];
		flight[0] = lt[0]-target_vec[0];
		flight[1] = 0; // On-axis
		flight[2] = lt[2]-target_vec[2];
		theta_left = -acos( dot(flight,khat)/mag(flight) );
		theta_left += theta_central;

		flight[0] = rt[0]-target_vec[0];
		flight[1] = 0; // On-axis
		flight[2] = rt[2]-target_vec[2];
		theta_right = acos( dot(flight,khat)/mag(flight) );
		theta_right += theta_central;


		/* Set scattering angle based (loosely) on Rutherford. */
		/* Determine Bounds for theta */
		theta_right = 1./pow( sin(theta_right/2.),4 );
		theta_left = 1./pow( sin(theta_left/2.),4 );

		/* Choose uniform deviate. */
		theta = (theta_right-theta_left);
		theta *= ( (double)rand())/( (double)RAND_MAX);
		theta += theta_left;

		/* Fold in Beam Energy dependence and transform uniform 
		 * to weighted theta. */
		KE = (beam_energy/mean_beam_energy);
		theta = sqrt( sqrt(theta)*KE  ) ;
		theta = 2.*asin( ( 1./theta ) );

		/* Choose uniform Phi...doesn't take into account detector 
		 * acceptance. */
		phi = 0.1*( (double)rand())/( (double)RAND_MAX)-0.05;		

		/* Dump result of each loop to STDOUT. */
#pragma omp barrier
		printf("%e %e  %e %e\n",beam_energy,target_position,theta,phi);


	}

	return 0;
}
