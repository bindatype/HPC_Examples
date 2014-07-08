        PROGRAM random

        INTEGER ISEED,nu 
        REAL X(10)

      
        CALL RANDOM_SEED   (SIZE=ISEED) 
        CALL RANDOM_NUMBER (HARVEST=X)

        write (*,*) X
         
        END PROGRAM random
