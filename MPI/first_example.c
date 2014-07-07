#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char *hostname;
	int thread_id,number_of_threads;
	double time_initial,time_current,time;
	if(NULL == (hostname = malloc(80*sizeof(char)))){puts("Malloc Failed!");exit(21);}
	MPI_Init(&argc,&argv);
	time_initial  = MPI_Wtime();

	MPI_Comm_rank(MPI_COMM_WORLD, &thread_id);
	MPI_Comm_size(MPI_COMM_WORLD, &number_of_threads);
	gethostname(hostname,80);

	printf("Hostname: %s \t HostID %ld, Page Size: %d\n",hostname, gethostid(),getpagesize());
	time_current  = MPI_Wtime();
	time  = time_current - time_initial;
	printf("Thread: %d out of %d;\tDuration: %f\n",thread_id, number_of_threads,time);
	MPI_Finalize();
	free(hostname); 
	return 0;
}

