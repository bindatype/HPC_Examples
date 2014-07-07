#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#ifndef _SIZE
#define _SIZE 16
#endif

int main(int argc, char **argv) {

	MPI_Init(&argc,&argv);

	int i,j;
	int CPUs, rank;
	double **m;
	m = malloc( _SIZE * sizeof(double *));
	*m = malloc( _SIZE * _SIZE * sizeof(double));
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&CPUs);

	for ( i = 0; i < _SIZE; i++ )
		m[i] = *m + i*_SIZE;

	if ( 0 == rank ) {
		for ( i = 0; i < _SIZE; i++ )
			for ( j = 0; j < _SIZE; j++ )
				*(*(m+i)+j) = i + j;
	}

	if ( 0 == rank ) {
		//    printf("Procs: %d\n",CPUs);

		for ( i = 0; i < _SIZE; i++ )
			for ( j = 0; j < _SIZE; j++ )
				printf("*(*(m+%d)+%d) = %p %p %f\n",i,j,((m+i)+j),(*(m+i)+j),*(*(m+i)+j));
	} 

	MPI_Finalize();
	free(*m);
	free(m);
	return 0;
}
