#!/bin/bash


#SBATCH -o R_test%j.out
#SBATCH -e R_test%j.err

#SBATCH -t 10
#SBATCH -p defq
#SBATCH	 -N 4
#SBATCH  -n 64

cd /home/maclach/Codes/HPC_Examples/SLURM/SingleThreadSRun/R_Exampl 
#cd /home/maclach/Codes/HPC_Examples/SLURM/SingleThreadSRun/R_Example 
srun sh wrapper.sh
