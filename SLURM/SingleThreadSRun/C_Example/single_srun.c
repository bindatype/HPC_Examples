#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <bits/local_lim.h>

int main(int argc, char **argv) {
	char hostname[HOST_NAME_MAX];
	gethostname(hostname,HOST_NAME_MAX); 
	if (3 != argc ) exit(2);
        int task,size;
	task = atoi(argv[1]);
	size = atoi(argv[2]);
	
	printf("I am single-thread process %d of %d on %s.\n",task,size,hostname);	

	return 0;

}
