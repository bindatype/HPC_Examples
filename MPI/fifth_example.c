/*
   In this example, we allocate a number of CPUs and 
   pass a string around to each CPU in the order they 
   are ranked. Each CPU adds its rank to the string 
   */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

// Set size of string to pass to each process 
#define STRING_SZ 200


int main(void)
{
	int rank,CPUs;
	double start, end, duration;
	//  MPI_Status status;
	char num[4];
	char *string;
	string = malloc( STRING_SZ * sizeof (char) );
	MPI_Init (NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&CPUs);

	start = MPI_Wtime(); 
	if ( 0 == rank )
	{
		sprintf(string,"R:%d",rank);
		for ( int i = 0; i < CPUs; i++ )
			MPI_Send(string,STRING_SZ,MPI_CHAR,1,i,MPI_COMM_WORLD);
		MPI_Recv(string,STRING_SZ,MPI_CHAR,CPUs-1,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);  
		end = MPI_Wtime();
		duration = end - start;
		printf("%s\n",string);
		printf("Duration: %f\n",duration);
	} else {
		MPI_Recv(string,STRING_SZ,MPI_CHAR,rank-1,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
		sprintf(num,"_%d",rank); 
		strcat(string,num);     
		if (rank + 1 < CPUs ) {
			MPI_Send(string,STRING_SZ,MPI_CHAR,rank+1,1,MPI_COMM_WORLD);
		} else {
			MPI_Send(string,STRING_SZ,MPI_CHAR,0,1,MPI_COMM_WORLD);
		}
	}





	MPI_Finalize();
	return 0;
}
