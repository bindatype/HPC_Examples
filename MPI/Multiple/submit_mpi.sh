#!/bin/bash

#SBATCH -o testing%j.out
#SBATCH -e testing%j.err 
#SBATCH -N 50
#SBATCH -p defq
#SBATCH -t 00:30:00
#SBATCH --mail-type=ALL
#SBATCH --mail-user=maclach@gwu.edu

module load openmpi/1.8/gcc/4.7/cpu

mpirun -n 800 ./multiple 


