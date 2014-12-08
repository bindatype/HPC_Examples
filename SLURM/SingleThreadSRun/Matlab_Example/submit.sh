#!/bin/bash


#SBATCH -p short
#SBATCH -t 30
#SBATCH	 -N 2
#SBATCH  -n 32

### Be sure to change this option to the working directory for your own codes!
#SBATCH  -D /home/maclach/Codes/HPC_Examples/SLURM/SingleThreadSRun/Matlab_Example


srun sh wrapper.sh
