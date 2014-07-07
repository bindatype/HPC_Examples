#include <stdio.h>
#include <mpi.h>

#define SIZE 100

int main(int argc, char **argv) 
{
	int size, rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	char my_string[100];
	int i;

	//  printf("Starting %d out of %d\n",rank,size);

	if ( 0 == rank ) {
		printf("Manager\n");
// Put a bug in for fun. 
		for ( i = 0; i < size; i++) //{ 
			sprintf(my_string,"\tMessage to Rank %d.\n",i);
			MPI_Send(my_string,100,MPI_CHAR,i,i,MPI_COMM_WORLD);
	//	}
	} else {
		MPI_Recv(my_string,100,MPI_CHAR,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		printf("Process %d Msg Rcvd:%s\n",rank,my_string);
	}


	MPI_Finalize();

	return 0;
}
