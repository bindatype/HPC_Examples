#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string.h> //nsight doesn't give error if this isnt' included. ?!!
#include <omp.h>

#define GRID_X 1
//#define GRID_Y 100000
#define GRID_Y 10
#define GHOSTS 2



using namespace std;

int main(){
	long clk0;
	clk0 = 1000*omp_get_wtime();
	long clk1;
	long clk2;
	long clk3;
	long clk4;
	long clk5;
	long clk6;
	long clk7;
	long clk8;
	long clk9;
	long clk10;
	long clk99;

	//	int tid;
	time_t t;
	float *grid,*grid_inv,*grid_new;
	if (NULL == (grid = (float*) malloc( (GRID_X+GHOSTS)*(GRID_Y+GHOSTS) * sizeof(float) ) ) ) { puts("GRID MEM FAIL");exit(1);}
	if (NULL == (grid_inv = (float*) malloc( (GRID_X+GHOSTS)*(GRID_Y+GHOSTS) * sizeof(float) ) ) ) { puts("GRID_INV MEM FAIL");exit(1);}
	if (NULL == (grid_new = (float*) malloc( (GRID_X+GHOSTS)*(GRID_Y+GHOSTS) * sizeof(float) ) ) ) { puts("GRID_NEW MEM FAIL"); exit(1);}
	

	int numthreads;
	clk1 = 1000*omp_get_wtime();
puts("1:/");
	#pragma omp parallel num_threads(4)
	{
		srand((unsigned) time(&t));
		int id = omp_get_thread_num();
		int nthreads = omp_get_num_threads();
		if ( 0 == id ) numthreads = nthreads;
cout << id*(GRID_Y+GHOSTS) << endl;
//		for (int i = id*(GRID_Y+GHOSTS); i < (id+1)*(GRID_Y+GHOSTS);i++){ 
		for ( int i = 0 ; i < GRID_Y + GHOSTS; i++ ) {
//#pragma omp parallel for num_threads(2)
			for ( int j = 0 ; j < GRID_X + GHOSTS; j++ ) {
//							cout << "Num THreads: "<<  id << "/"<<nthreads	 << endl;
				//			grid[i*(GRID_X+GHOSTS) + j] = grid_new[i*(GRID_X+GHOSTS) + j] = rand() / ((float) RAND_MAX) ;
				//grid_inv[j*(GRID_X+GHOSTS) + i] = grid[i*(GRID_X+GHOSTS) + j] = rand() / ((float) RAND_MAX) ;
				grid[i*(GRID_X+GHOSTS) + j] = rand() / ((float) RAND_MAX) ;

			}
		}
	}
	clk2 = 1000*omp_get_wtime();
puts("2:/");
//#pragma omp parallel
	{
//#pragma omp for
		for (int i = 1; i < GRID_Y+GHOSTS; i++ ){
			grid[i*(GRID_X+GHOSTS)] = 1.2;
			grid[(i+1)*(GRID_X+GHOSTS)-1] = 1.3;
		}
	}
	clk3 = 1000*omp_get_wtime();

puts("3:/");


//#pragma omp parallel
//	{
#pragma omp parallel for num_threads(24)
		for (int i = 1; i < GRID_Y+GHOSTS; i++ ){
			grid[(i+1)*(GRID_X+GHOSTS)-1] = 1.3;
		}
//	}
	clk4 = 1000*omp_get_wtime();

puts("4:/");
#pragma omp parallel for num_threads(32)
	for (int j = 0; j < GRID_X+GHOSTS; j++ ){
		grid[j] = 1.;
	}
	clk5 = 1000*omp_get_wtime();

puts("5:/");
	#pragma omp parallel for
	for (int j = 0; j < GRID_X+GHOSTS; j++ ){
		grid[(GRID_Y+GHOSTS-1)*(GRID_X+GHOSTS)+j]=0.85;
	}
	clk6 = 1000*omp_get_wtime();

puts("6:/");
/*	for ( int i = 0 ; i < GRID_Y + GHOSTS; i++ ) {
		for ( int j = 0 ; j < GRID_X + GHOSTS; j++ ) {
						printf ("%f ",grid[i*(GRID_X+GHOSTS)+j]);
		}
				printf ("\n");
	}
	printf ("\n");*/

	memcpy(grid_new,grid,(GRID_X+GHOSTS)*(GRID_Y+GHOSTS) * sizeof(float)); // THis makes annoying uninit msg go away
	//		printf("grid size in bytes %d\n",(GRID_X+GHOSTS)*(GRID_Y+GHOSTS) * sizeof(float));

	clk7 = 1000*omp_get_wtime(); 

puts("7:/");
#pragma omp parallel for num_threads(32)
	for ( int i = 1 ; i < GRID_Y + GHOSTS-1; i++ ) {
		for ( int j = 1 ; j < GRID_X + GHOSTS-1; j++ ) {
			grid_new[i*(GRID_X+GHOSTS) + j] 
				= 0.25*(grid[i*(GRID_X+GHOSTS) 
				+ j-1]+grid[i*(GRID_X+GHOSTS) + j+1] 
				+ grid[(i-1)*(GRID_X+GHOSTS) + j]
				+ grid[(i+1)*(GRID_X+GHOSTS) + j]);
		}
		//		printf ("\n");
	}
	clk8 = 1000*omp_get_wtime();

puts("8:/");
/*	for ( int i = 0 ; i < GRID_Y + GHOSTS; i++ ) {
		for ( int j = 0 ; j < GRID_X + GHOSTS; j++ ) {
						printf ("%f ",grid_new[i*(GRID_X+GHOSTS)+j]);
		}
				printf ("\n");
	}
		printf ("\n");*/

	memcpy(grid,grid_new,(GRID_X+GHOSTS)*(GRID_Y+GHOSTS) * sizeof(float));

        clk9 = 1000*omp_get_wtime();

puts("9:/");
#pragma omp parallel for num_threads(24)
        for ( int i = 1 ; i < GRID_Y + GHOSTS-1; i++ ) {
                for ( int j = 1 ; j < GRID_X + GHOSTS-1; j++ ) {
                        grid_new[i*(GRID_X+GHOSTS) + j] 
                                = 0.25*(grid[i*(GRID_X+GHOSTS) 
                                + j-1]+grid[i*(GRID_X+GHOSTS) + j+1] 
                                + grid[(i-1)*(GRID_X+GHOSTS) + j]
                                + grid[(i+1)*(GRID_X+GHOSTS) + j]);
                }
                //              printf ("\n");
        }
                


/*	for ( int i = 0 ; i < GRID_Y + GHOSTS; i++ ) {
		for ( int j = 0 ; j < GRID_X + GHOSTS; j++ ) {
						printf ("%f ",grid_new[i*(GRID_X+GHOSTS)+j]);
		}
				printf ("\n");
	}*/

        clk10 = 1000*omp_get_wtime();

puts("10:/");
	memcpy(grid,grid_new,(GRID_X+GHOSTS)*(GRID_Y+GHOSTS) * sizeof(float));

	//			printf ("\n");

#pragma omp parallel for num_threads(24)
        for ( int i = 1 ; i < GRID_Y + GHOSTS-1; i++ ) {
                for ( int j = 1 ; j < GRID_X + GHOSTS-1; j++ ) {
                        grid_new[i*(GRID_X+GHOSTS) + j]
                                = 0.25*(grid[i*(GRID_X+GHOSTS)
                                + j-1]+grid[i*(GRID_X+GHOSTS) + j+1]
                                + grid[(i-1)*(GRID_X+GHOSTS) + j]
                                + grid[(i+1)*(GRID_X+GHOSTS) + j]);
                }
                //              printf ("\n");
        }
                




	for ( int i = 0 ; i < GRID_Y + GHOSTS; i++ ) {
		for ( int j = 0 ; j < GRID_X + GHOSTS; j++ ) {
						printf ("%f ",grid_new[i*(GRID_X+GHOSTS)+j]);
		}
				printf ("\n");
	}

	free(grid_inv);
	free(grid_new);
	free(grid);

	clk99 = 1000*omp_get_wtime();
	printf("\n Loop 2,1:\t%ld [ms]\n Loop 3,2:\t%ld [ms]"
			"	\n Loop 4,3:\t%ld [ms]"
			"	\n Loop 5,4:\t%ld [ms]"
			"	\n Loop 6,5:\t%ld [ms]"
			"	\n Memcpy 7,6:\t%ld [ms]"
			"	\n Loop 8,7:\t%ld [ms]"
			"	\n Memcpy 9,8:\t%ld [ms]"
			"	\n Loop 10,9:\t%ld [ms]"
			"	\n TOTAL: \t%ld [ms]\n",
			clk2-clk1,
			clk3-clk2,
			clk4-clk3,
			clk5-clk4,
			clk6-clk5,
			clk7-clk6,
			clk8-clk7,
			clk9-clk8,
			clk10-clk9,
			clk99-clk0);
	//		(int)((clk3-clk2)/((double)CLOCKS_PER_SEC)),
	//		(int)((clk3-clk1)/((double)CLOCKS_PER_SEC)));

	return 0;
}
