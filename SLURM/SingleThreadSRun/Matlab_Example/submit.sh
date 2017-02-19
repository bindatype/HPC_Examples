#!/bin/bash


#SBATCH -p debug
#SBATCH -t 30
#SBATCH	 -N 2
#SBATCH  -n 28

### Be sure to change this option to the working directory for your own codes!
#SBATCH  -D /home/maclach/Codes/HPC_Examples/SLURM/SingleThreadSRun/Matlab_Example


srun sh wrapper.sh
