#!/bin/bash
#SBATCH -A <account>
#SBATCH -N 1
#SBATCH -n 2
#SBATCH --time=00:30:00 

# Use '&' to move the first job to the background
srun -n 1 ./job1.batch &
srun -n 1 ./job2.batch 

# Use 'wait' as a barrier to collect both executables when they are done.
wait
