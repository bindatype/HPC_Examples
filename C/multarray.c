#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
        unsigned int numrows ;
        unsigned int numcols ;
        unsigned int i,j;

//-- Do sane argument checking and usage messages!

        switch(argc){
           case 3:
                numrows = atoi(argv[1]);
                numcols = atoi(argv[2]);
                break;
           default:
                printf("Usage: ./glensexample [int numrows] [int numcols] \n");
                exit(11);
        }


//-- Two calls to malloc

//-- Two lines are equivalent.
//        int **myarray = malloc(numrows * sizeof(int *));
        int **myarray; myarray = malloc(numrows * sizeof(int *));
	if (NULL == myarray) {
           printf("Could not allocate array\n");
	   exit(21);
        } 
        *(myarray) = malloc(numrows * numcols * sizeof(int));
        if (NULL == *(myarray) ) {
           printf("Could not allocate array\n");
           exit(21);
        } 
	
//-- Point the pointers using pointer arithmetic
        for(i = 1; i < numrows; i++){
                *(myarray + i) = *myarray + i * numcols;
        }

//-- This loop doesn't count toward malloc or free calls
//-- I'm just filling the array here.

        for(i = 0; i < numrows; i++){
                for (j=0; j<numcols; j++){
                        myarray[i][j]=i+j+1;
                        printf("%d ",myarray[i][j]);
                }
                printf("\n");
        }

//-- Do garbage collection

        free((void *)myarray[0]);
        free((void *)myarray);

return 0;
}
