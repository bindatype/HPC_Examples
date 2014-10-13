#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

	if (3 != argc ) exit(2);
        int task,size;
	task = atoi(argv[1]);
	size = atoi(argv[2]);
	
	printf("I am single-thread process %d of %d.\n",task,size);	

	return 0;

}
