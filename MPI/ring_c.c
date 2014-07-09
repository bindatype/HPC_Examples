/*
 * Copyright (c) 2004-2006 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2006      Cisco Systems, Inc.  All rights reserved.
 *
 * Simple ring test program
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define _SIZE 8000000

int main(int argc, char *argv[])
{
    int rank, size, tag = 201;

    /* Start up MPI */

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
	

    double *message,duration;
    message = (double *) malloc(sizeof(double) * _SIZE );
 
    /* Calculate the rank of the next process in the ring.  Use the
       modulus operator so that the last process "wraps around" to
       rank zero. */
	
	int count = 0;	
	for ( int dest = rank+1; dest < size; dest++ ) {
		++count;
		message[dest+rank*size] = MPI_Wtime(); 
//		if ( 0 == rank ) printf("Index: %d Rank:%d\n Dest:%d Count:%d",dest+rank*size,rank,dest,count);
//		if ( 0 == rank ) printf("Index: %d \n",dest+rank*size);
		MPI_Send(message,_SIZE,MPI_DOUBLE,dest,rank,MPI_COMM_WORLD);
	}

	char processor_name[MPI_MAX_PROCESSOR_NAME];
  	int name_len;
  	MPI_Get_processor_name(processor_name, &name_len);

        for ( int recv = 0; recv <rank ; recv++ ) {
                        MPI_Recv(message,_SIZE,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
                        duration = MPI_Wtime()- message[rank + status.MPI_SOURCE*size];
//                        message[status.MPI_SOURCE + (status.MPI_TAG+1)*size] = MPI_Wtime();
//                        printf("-> %d %d %f , %s %f [Mb/s] <-\n", status.MPI_SOURCE,rank,duration,processor_name,(double) (sizeof(double) * _SIZE * 8/1000000)/duration);
//                        printf("%d %d %f \n", status.MPI_SOURCE,rank,(double) (sizeof(double) * _SIZE * 8/1000000)/duration);
                        printf("%d %d %f %f %f\n", status.MPI_SOURCE,rank,(double) (sizeof(double) * _SIZE * 8/1048576)/duration,duration,(double) (sizeof(double) * _SIZE * 8/1048576));
			
        }


 
    /* All done */

    MPI_Finalize();
    return 0;
}
