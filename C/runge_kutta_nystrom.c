/* Runge Kutta Nystrom, Order 4-- Integrates second order differential equation. 
 * f(x(t),v(t),t)=d2x/dt2=func, v=dx/dt.
 *
 * Arguments to main: None 
 *	Returns int.
 * 
 * Arguments to rkn4: function pointer, array of x, initial value of x
 * 		      array of v, initial value of v, step size, number of steps.
 *	Returns nothing but fills columns of x and v.
 *	Called from main
 *
 * Arguments to function: x and v as computed in rkn as well as t.
 *		This is the function to be integrated.
 *	Returns value of f.
 * 	Called from rkn
 * 
 */ 


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double function(double x, double v, double t);
double (*func)(double x, double v, double t);

double rkn4(double (*func)(double x, double v, double t),
		double x[], double x0, double v[], double v0, double t, double h, long steps);

double function(double x, double v, double t){
	return -x*x; //Change this value to change integrand.
}


int main (){
	long steps = 1000; 				//Number of steps.
	double x0=0.,v0=1.,t,h=0.001; 			//Initial position, initial velocity, time, step size.
	double *x = malloc(steps * sizeof(double)); 	//Position array
	double *v = malloc(steps * sizeof(double)); 	//Velocity array

	/* Set pointer to point at the function to integrate. */
	func = function;

	/* Do integration. */
	rkn4(func,x,x0,v,v0,t,h,steps);

	/* Print results to STDOUT */
	long int i;
	for ( i=0; i<steps; ++i){
		printf(" %ld %e %e\n",i,x[i],v[i]);
	}


	return 0;
}

double rkn4(double (*func)(double x, double v, double t), 
		double x[], double x0, double v[],double v0, double t, double h, long steps)
{
	double k1,k2,k3,k4;

	x[0] = x0; //Initial position
	v[0] = v0; //Initial velocity

	long i;
	for ( i=1; i<steps; ++i){
		k1 = func(x[i-1],v[i-1],t);	
		k2 = func(x[i-1]+h*v[i-1]/2.+h*h*k1/8.,v[i-1]+h*k1/2.,t+h/2.);
		k3 = func(x[i-1]+h*v[i-1]/2.+h*h*k1/8.,v[i-1]+h*k2/2.,t+h/2.);
		k4 = func(x[i-1]+h*v[i-1]+h*h*k3/2.,v[i-1]+h*k3,t+h);

		x[i] = x[i-1] + h*v[i-1] + h*h*(k1+k2+k3)/6.;
		v[i] = v[i-1] + h*(k1 + 2.*k2 + 2.*k3 + k4)/6.;
		t+=h;
	}

	return 0;
}
