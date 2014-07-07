#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>

#ifndef _SIZE
#define _SIZE 100
#endif

#define _BSD_SOURCE

#define byte_size 8

int main() {

	char *hostname;
	int rank, size;
	double a[_SIZE] , b[_SIZE], w_a[_SIZE] ;
	double start, end, duration;
	hostname = malloc(80*sizeof(char));  

	MPI_Init(0,0);
	MPI_Status status;

	MPI_Comm_rank (MPI_COMM_WORLD,&rank);
	MPI_Comm_size (MPI_COMM_WORLD,&size);

	start = MPI_Wtime();
	if ( 0 == rank ) {
		start = MPI_Wtime(); 
		MPI_Send(a,_SIZE,MPI_DOUBLE,1,0,MPI_COMM_WORLD);
		MPI_Recv(b,_SIZE,MPI_DOUBLE,1,0,MPI_COMM_WORLD,&status);
		end = MPI_Wtime();
	} else if ( 1 == rank ) {
		MPI_Recv(w_a,_SIZE,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&status);
		MPI_Send(w_a,_SIZE,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}
	gethostname(hostname,80);
	printf("Hostname: %s \n",hostname);	
	MPI_Finalize();

	duration = end - start;

	if ( 0 == rank ) 
		printf("%ld %f %f\n",(long)byte_size * _SIZE/1000000,duration,(long)byte_size * _SIZE/1000000/duration);

	return 0;
}
