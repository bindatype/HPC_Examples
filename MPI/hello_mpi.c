#include <stdio.h>
#include <mpi.h>


int main(int argc, char **argv){

	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	printf("Hello from rank %d out of %d\n",rank, size);

	char received[100];
	char message[100]="Hello";

	if ( 0 == rank ) 
		MPI_Send(message,100,MPI_CHAR,1,0,MPI_COMM_WORLD);

	if ( 1 == rank){
		MPI_Recv(received,100,MPI_CHAR,0,MPI_ANY_TAG,MPI_COMM_WORLD,NULL); 
	        printf("String is %s\n",received);   
	}

	MPI_Finalize();
	return 0;
}
