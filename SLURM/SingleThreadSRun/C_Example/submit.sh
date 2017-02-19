#!/bin/bash


#SBATCH -p debug
#SBATCH -t 30
#SBATCH --array=1-10
#SBATCH	 -N 2
#SBATCH  -n 28


srun sh wrapper.sh
