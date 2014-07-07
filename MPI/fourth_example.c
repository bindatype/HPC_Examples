/* salloc -t 00:01:00 mpirun -np 5 ./fourth_example */  
#include <stdio.h>
#include <mpi.h>

#define SIZE 4

int main(int argc, char **argv) 
{
	int size, rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	int i,j;
	double m[SIZE][SIZE];
	double x[SIZE],y[SIZE],a[SIZE]; 

	//  printf("Starting %d out of %d\n",rank,size);

	if ( 0 == rank ) {
		for ( i = 0; i < SIZE; i++ ){
			for ( j = 0; j < SIZE; j++ )
				*( *(m+j)+i) = i;	
		}
		for ( i = 0; i < SIZE; i++)
			MPI_Send(*(m+i),SIZE,MPI_DOUBLE,i+1,i,MPI_COMM_WORLD);

	} else {
		MPI_Recv(a,SIZE,MPI_DOUBLE,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		for ( i = 0; i < SIZE; i++ )
		{
			y[i] = a[i]*a[i];
			printf("%f ",y[i]);
		}
		printf("\n");
		MPI_Send(y,SIZE,MPI_DOUBLE,0,i,MPI_COMM_WORLD);

	}
	MPI_Reduce(y,x,SIZE,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	/*  if ( 0 == rank )
	    for ( i = 0; i < SIZE; i++ )
	    {
	    printf("%f \n",*(x+i));
	    }
	    */

	MPI_Finalize();

	return 0;
}
