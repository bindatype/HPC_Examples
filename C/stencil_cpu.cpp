#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string.h> //nsight doesn't give error if this isnt' included. ?!!

#define GRID_X 5
#define GRID_Y 5
#define GHOSTS 2
#define NUMITER 4


void init_mesh(float *grid) {

	time_t t;
	srand((unsigned) time(&t));

	for ( int i = 0 ; i < GRID_Y + GHOSTS; i++ ) {
		for ( int j = 0 ; j < GRID_X + GHOSTS; j++ ) {
			grid[i*(GRID_X+GHOSTS) + j] = rand() / ((float) RAND_MAX) ;
		}
	}

	for (int i = 1; i < GRID_Y+GHOSTS; i++ ){
		grid[i*(GRID_X+GHOSTS)] = 1.-((float)i)/(GRID_Y+GHOSTS-1);
		grid[(i+1)*(GRID_X+GHOSTS)-1] = 1.0;
	}

	for (int j = 0; j < GRID_X+GHOSTS; j++ ){
		grid[j] = 1.0;
	}

	for (int j = 0; j < GRID_X+GHOSTS; j++ ){
		grid[(GRID_Y+GHOSTS-1)*(GRID_X+GHOSTS)+j]=(float)j/( GRID_X + GHOSTS -1) ;
	}

	for (int i = 1; i < GRID_Y+GHOSTS; i++ ){
		grid[(i+1)*(GRID_X+GHOSTS)-1] = 1.;
	}
}

void scan_mesh(float *grid, float *grid_new) {
	for ( int i = 1 ; i < GRID_Y + GHOSTS-1; i++ ) {
		for ( int j = 1 ; j < GRID_X + GHOSTS-1; j++ ) {
			grid_new[i*(GRID_X+GHOSTS) + j] 
				= 0.25*(grid[i *(GRID_X+GHOSTS) + j-1]
						+ grid[i*(GRID_X+GHOSTS) + j+1] 
						+ grid[(i-1)*(GRID_X+GHOSTS) + j]
						+ grid[(i+1)*(GRID_X+GHOSTS) + j]);
		}
	}
}

void print_mesh(float *mesh) {
	for ( int i = 0 ; i < GRID_Y + GHOSTS; i++ ) {
		for ( int j = 0 ; j < GRID_X + GHOSTS; j++ ) {
			printf ("%f ",mesh[i*(GRID_X+GHOSTS)+j]);
		} printf ("\n");
	} printf ("\n");
}

using namespace std;

int main(){
	float *grid,*grid_new;
	if (NULL == (grid = (float*) malloc( (GRID_X+GHOSTS)*(GRID_Y+GHOSTS) * sizeof(float) ) ) ) 
	{ puts("GRID MEM FAIL");exit(1);}
	if (NULL == (grid_new = (float*) malloc( (GRID_X+GHOSTS)*(GRID_Y+GHOSTS) * sizeof(float) ) ) ) 
	{ puts("GRID_NEW MEM FAIL"); exit(1);}

	init_mesh(grid);
	print_mesh(grid);

	memcpy(grid_new,grid,(GRID_X+GHOSTS)*(GRID_Y+GHOSTS) * sizeof(float)); // THis makes annoying uninit msg go away

	/* Main iteration loop */

	for (int i = 0; i < NUMITER; i++) {
		scan_mesh(grid,grid_new);
		memcpy(grid,grid_new,(GRID_X+GHOSTS)*(GRID_Y+GHOSTS) * sizeof(float));
		print_mesh(grid);
	}

	free(grid_new);
	free(grid);

	return 0;
}
