#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "comp-phys.h"


double dot(double vec1[],double vec2[]){

        return vec1[0]*vec2[0]+vec1[1]*vec2[1]+vec1[2]*vec2[2];
}

double mag(double vec[]){
        
        return sqrt( dot(vec,vec) );
}

double raise(double a, int b){

        double answer=1;
        int i;
        for(i=0;i<b;i++){
                answer*=a;
        }

        if ( b < 0 ){
                return 1./answer;
        }
        else{
                return answer;
        }
}

double getrandom(){
        srand((unsigned)time(NULL)); 
        return ((double) rand())/((double) RAND_MAX);
}


#ifndef _COMP_PHYS_H
#define COMP_PHYS_H

extern double dot(double vec1[],double vec2[]);
extern double mag(double vec[]);
extern double raise(double a, int b);
extern double getrandom();
#endif
