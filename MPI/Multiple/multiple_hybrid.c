/*
 * Test this example with 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h>
#include <bits/local_lim.h>

#define COLS (5)
#define ROWS (1024)

extern double get_change(double *x, double *y, int n);
extern void relax(double *dest, double *srce, int cols, int rows);
extern void init_grid(double **,double **,int cols, int rows);
extern void init_boundaries(double *,int,int);
extern void print_buffer(double *,int,int);

int main(int argc, char **argv) {
//        char hostname[HOST_NAME_MAX];
//        gethostname(hostname,HOST_NAME_MAX); 
//	printf("Hostname: %s\n",hostname);
	int size, rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if (size > ROWS ) {puts("Too many tasks for size!"); exit(10);}
	int subROWS = ROWS/size;
	double *local,*local_new;
	double  *p,*p_new;

	init_grid(&local,&local_new,COLS,subROWS+2);
	if (0 == rank) {
		init_grid(&p,&p_new,COLS,ROWS+2);
		init_boundaries(p,COLS,ROWS+2); 
		memmove(p_new,p, COLS*(ROWS+2) * sizeof(double) );
		print_buffer(p_new,COLS,ROWS+2);
	}

	/* Wait for everyone to get here. */
	MPI_Barrier(MPI_COMM_WORLD);

	/* Distribute data */
	if (0 == rank ) 
		for (int j=0; j < size; j++) 
			MPI_Send(p+j*subROWS*COLS, (subROWS+2)*COLS,MPI_DOUBLE,j,0,MPI_COMM_WORLD);
	MPI_Recv(local,(subROWS+2)*COLS,MPI_DOUBLE,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);


	/* Do some work */
	register int count = 1000;
	int up_nbr, dn_nbr ;
	double *firstbuf, *lastbuf;
	init_grid(&firstbuf,&lastbuf,COLS,1);
	while (count-- > 0) {
		relax(local_new,local,COLS,subROWS+2);

		memmove(lastbuf,local_new ,COLS*sizeof(double));
		memmove(firstbuf,local_new + (subROWS+1)*COLS,COLS*sizeof(double));
		
		up_nbr = (rank == size - 1) ? MPI_PROC_NULL : rank + 1; 
		dn_nbr = (rank == 0) ? MPI_PROC_NULL : rank - 1; 
		MPI_Sendrecv(local_new + (1)*COLS ,COLS,MPI_DOUBLE, dn_nbr,0,firstbuf,COLS,MPI_DOUBLE,up_nbr,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		MPI_Sendrecv(local_new+(subROWS)*COLS,COLS,MPI_DOUBLE,up_nbr,0,lastbuf,COLS,MPI_DOUBLE,dn_nbr,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		MPI_Barrier(MPI_COMM_WORLD);

		memmove(local_new ,lastbuf,COLS*sizeof(double));
		memmove(local_new + (subROWS+1)*COLS,firstbuf,COLS*sizeof(double));
		//		/*For Debugging*/	memmove(local_new,local, COLS*(subROWS+2) * sizeof(double) );

		// Copy updated grid into "present-time" grid.		
		memmove(local,local_new,COLS*(subROWS+2)*sizeof(double));
	}


	/* Send local buffers back to main process. */
	MPI_Send(local_new+1*COLS,(subROWS)*COLS,MPI_DOUBLE,0,(subROWS+2),MPI_COMM_WORLD);
	/* Main process receives local buffers. */
	if ( 0 == rank ) 
		for ( int i =0; i < size; i++) {
			MPI_Probe(MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
			MPI_Recv(p_new+(status.MPI_SOURCE*subROWS+1)*COLS,(subROWS)*COLS,MPI_DOUBLE,status.MPI_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		}

	// Print out the results.
	if ( 0 == rank ){
		// /* Uncomment for debugging. */ print_buffer(p,COLS,ROWS+2);
		print_buffer(p_new,COLS,ROWS+2);
		if ( 0 == rank ) {
			free(p_new); 
			free(p); 
		}
	}
	free(local);
	free(local_new);
	MPI_Finalize();

	return 0; 
}

void relax(double *dest,double *srce,int cols,int rows){
	memmove(dest,srce, cols*rows * sizeof(double) );
	for ( int j = 1 ; j < rows-1; j++) 
		for ( int i = 1 ; i < cols-1; i++) 
			dest[i+j*cols] = 0.25*(srce[i-1+j*cols]+srce[i+1+j*cols]+srce[i+(j-1)*cols]+srce[i+(j+1)*cols]);
}

void init_boundaries(double *l_p,int cols,int rows){ 
/*	for ( int i = 0 ; i < cols; i++) {
		l_p[i] = -1;
		l_p[i + cols*(rows -1)] = 1;
	}

	for ( int i = 0 ; i < rows; i++) {
		l_p[i*cols] = -1;
		l_p[(i+1)*cols -1] = 1; //column
		// l_p[i*(cols-1)+rows-1] = -1; //diagonal
	}
*/
        for (int i = 0 ; i < cols*rows; i++ )
                l_p[i] = 0;
        l_p[cols/2] = 1;
}

void init_grid(double **p, double **p_new, int cols, int rows){
	if (NULL == (*p = malloc(  cols*(rows) * sizeof(double) )  )  ) {
		puts("Allocation Error.");
		exit(99);
	}
	if (NULL == (*p_new = malloc( cols*(rows) * sizeof(double)))) {
		puts("Allocation Error.");
		exit(99);
	}
	for ( int i = 0 ; i < cols*(rows); i++){

		(*p)[i] = 0.;//(i) ;
		(*p_new)[i] = 0.;//i*i ;
	}
}

void print_buffer(double *p, int cols, int rows){
	puts(" ");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%f\t",p[i*cols+j]);
		}
		printf("\tRow: %d",i);
		puts(" ");
	}


}
/*
   double get_change(double *x, double *y, int n){
   double result=0.;
   for (int i=0; i<n;i++)
   result+=x[i]*x[i]-y[i]*y[i];
   return result;
   }
   */
