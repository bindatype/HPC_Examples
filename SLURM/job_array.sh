#!/bin/bash

#SBATCH -o JobArray_Test%j-%A_%a.out
#SBATCH -e JobArray_Test%j-%A_%a.err
#SBATCH -p secret
#SBATCH -N 1
# SBATCH -n 8
#SBATCH --export=NONE
#SBATCH -t 0:10:00
#SBATCH --array=1-16


 echo $SLURM_JOBID $SLURM_ARRAY_TASK_ID $SLURM_ARRAY_JOB_ID >> output
#mkdir $SLURM_JOBID
#cd $SLURM_JOBID
#cd ..

