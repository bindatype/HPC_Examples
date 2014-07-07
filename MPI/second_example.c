#include <stdio.h>
#include <mpi.h>
#include "math.h"

#define SIZE 10
#define MIN(x,y) ((x) < (y) ? x : y)

void manager(int numprocs)
{
	double a[SIZE][SIZE];
	double c[SIZE];
	int i, j , sender, row, numsent = 0;
	double dotp;
	MPI_Status status;

	for (i=0; i<SIZE; i++ )
		for(j=0; j < SIZE; j++)
			a[i][j] = (double) j;

	for (i = 1; i < MIN(numprocs,SIZE); i++) 
	{
		MPI_Send(a[i-1],SIZE,MPI_DOUBLE, i, i, MPI_COMM_WORLD);
		numsent++;
	}

	for (i=0; i<SIZE; i++ )
	{
		MPI_Recv(&dotp, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
		sender = status.MPI_SOURCE;
		row = status.MPI_TAG-1;
		c[row] = dotp;

		// Send another row to worker if there is one to send
		if(numsent < SIZE )
		{
			MPI_Send(a[numsent],SIZE,MPI_DOUBLE, sender, numsent + 1, MPI_COMM_WORLD);

			printf("Number Sent: %d\n", numsent);
		}
		else
		{

			MPI_Send(MPI_BOTTOM,0,MPI_DOUBLE, sender, 0, MPI_COMM_WORLD);
		}
	}

}

void worker( void) 
{
	double b[SIZE],c[SIZE];
	int i,row, myrank;
	double dotp;
	MPI_Status status;

	for (i=0; i<SIZE; i++ )
		b[i] = 1.0;

	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	if (myrank < SIZE) 
	{
		MPI_Recv(c, SIZE, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
		while (status.MPI_TAG > 0)
		{
			printf("TAG: %d\n",status.MPI_TAG);
			row = status.MPI_TAG - 1;
			dotp = 0.0;
			for (i = 0; i < SIZE; i++ )
				dotp += c[i]*b[i];
			MPI_Send(&dotp,1,MPI_DOUBLE, 0, row + 1, MPI_COMM_WORLD);
			MPI_Recv(c, SIZE, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
		} 
	}


}

int main (int argc, char **argv) 
{

	int numprocs, myrank;

	MPI_Init(&argc,&argv);	
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs );
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);


	if (myrank == 0)
		manager(numprocs);
	else
		worker();
	MPI_Finalize();
	return 0;
}
