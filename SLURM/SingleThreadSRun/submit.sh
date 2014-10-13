#!/bin/bash


#SBATCH -p short
#SBATCH -t 300
#SBATCH	 -N 3
#SBATCH  -n 48

srun sh wrapper.sh
