#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define Steps 100000 /* Numbers of steps */


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


void rko4(double h, int Dim,
        void (*equations_of_motion)(double t, double Q[], double dQdt[]),
        double t, double Q0[], double Q[]) /* Runge-Kutta */
{
        int i;
        double *k1 = array(Dim), *k2 = array(Dim), *k3 = array(Dim), *k4 = array(Dim);
        double *Qa = array(Dim), *dQ = array(Dim);

        equations_of_motion(t, Q0, dQ);
        for(i = 0; i <= Dim - 1; i++)
        {
                k1[i] = dQ[i];
                Qa[i] = Q0[i] + h*k1[i]/2.;
        }

        equations_of_motion(t + 0.5 * h, Qa, dQ);
        for(i = 0; i <= Dim - 1; i++)
        {
                k2[i] = h * dQ[i];
                Qa[i] = Q0[i] + k2[i]/2.;
        }

        equations_of_motion(t + 0.5 * h, Qa, dQ);
        for(i = 0; i <= Dim-1; i++)
        {
                k3[i] = h * dQ[i];
                Qa[i] = Q0[i] + k3[i];
        }

        equations_of_motion(t + h, Qa, dQ);
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
	const double h = 0.01;
	const int Dim = 3;
        int i,step;
        double present_state[Dim],future_state[Dim];
		


      /* Initial state variables */
        present_state[0] = 10.;
        present_state[1] = 10.;
        present_state[2] = 10.;

      /* Main part */
        for(step = 0; step <= Steps - 1; step++)
        {
                for(i = 0; i <= Dim - 1; i++)
                {
                        printf("%f", present_state[i]);
                        (i == Dim - 1) ? putchar('\n') : putchar(' ');
                }
                rko4(h,Dim, user_def_func, h*step, present_state, future_state);
                memmove(present_state,future_state,Dim * sizeof(double));
        }
        return 0;
}

