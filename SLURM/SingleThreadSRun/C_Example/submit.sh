#!/bin/bash


#SBATCH -p defq,short
#SBATCH -t 30
#SBATCH	 -N 2
#SBATCH  -n 32

srun sh wrapper.sh
