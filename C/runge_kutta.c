#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define h 0.01 /* step size */
#define Steps 100000 /* Numbers of steps */

/* Dim is equal to the number of equations in user_def_func(). */ 
#define Dim 3 /* dimension of state variable */


void user_def_func( double t, double Q[], double dQdt[])
{
/* Q[0,1,2] = x,y,z */
        double sigma=10., b=8. / 3, r=28.;
        dQdt[0] = -sigma * Q[0] + sigma * Q[1];
        dQdt[1] = -Q[0] * Q[2] + r * Q[0] - Q[1];
        dQdt[2] = Q[0] * Q[1] - b * Q[2];
}


double *array(int Dim) /* Allocate memory for arrays */
{
      return (double *)malloc(Dim * sizeof(double));
}

void free_array(double *v) /* Free memory when done with arrays */
{
      free(v);
}

void swap_array(int Dim, double a[], double b[]) 
{
      int i;
      for(i = 0; i <= Dim - 1; i++) b[i] = a[i];
}

void rko4(double h, int Dim,
        void (*dQdt)(double t, double Q[], double dQdt[]),
        double t, double Q0[], double Q[]) /* Runge-Kutta */
{
        int i;
        double *k1 = array(Dim), *k2 = array(Dim), *k3 = array(Dim), *k4 = array(Dim);
        double *Qa = array(Dim), *dQ = array(Dim);

        dQdt(t, Q0, dQ);
        for(i = 0; i <= Dim - 1; i++)
        {
                k1[i] = h * dQ[i];
                Qa[i] = Q0[i] + k1[i]/2.;
        }

        dQdt(t + 0.5 * h, Qa, dQ);
        for(i = 0; i <= Dim - 1; i++)
        {
                k2[i] = h * dQ[i];
                Qa[i] = Q0[i] + k2[i]/2.;
        }

        dQdt(t + 0.5 * h, Qa, dQ);
        for(i = 0; i <= Dim-1; i++)
        {
                k3[i] = h * dQ[i];
                Qa[i] = Q0[i] + k3[i];
        }

        dQdt(t + h, Qa, dQ);
        for(i = 0; i <= Dim - 1; i++)
        {
                k4[i] = h * dQ[i];
                Q[i] = Q0[i] + (k1[i] + 2.*k2[i] + 2.*k3[i] + k4[i]) / 6.0;
        }

      /* Clean up */
        free_array(k1); free_array(k2); free_array(k3); free_array(k4);
        free_array(Qa); free_array(dQ);
}


int main()
{
        int i,step;
        double *Q0 = array(Dim),*Q1 = array(Dim);

      /* Initial state variables */
        Q0[0] = 10.;
        Q0[1] = 10.;
        Q0[2] = 10.;

      /* Main part */
        for(step = 0; step <= Steps - 1; step++)
        {
                for(i = 0; i <= Dim - 1; i++)
                {
                        printf("%f", Q0[i]);
                        if(i == Dim - 1) putchar('\n');
                        else putchar(' ');
                }
                rko4(h,Dim, user_def_func, h*step, Q0, Q1);
                swap_array(Dim, Q1, Q0);
        }
        return 0;
}

