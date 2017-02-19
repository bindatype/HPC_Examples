#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char *hostname;
	int rank,size;
	double time_initial,time_current,time;
	if(NULL == (hostname = malloc(80*sizeof(char)))){puts("Malloc Failed!");exit(21);}
	MPI_Init(&argc,&argv);
	time_initial  = MPI_Wtime();

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	gethostname(hostname,80);

	printf("Hostname: %s \t HostID %ld, Page Size: %d\n",hostname, gethostid(),getpagesize());
	time_current  = MPI_Wtime();
	time  = time_current - time_initial;
	printf("Thread: %d out of %d;\tDuration: %f\n",rank, size,time);
	MPI_Finalize();
	free(hostname); 
	return 0;
}

