#!/bin/bash

#SBATCH -o Tao_Test%j-%A_%a.out
#SBATCH -e Tao_Test%j-%A_%a.err
#SBATCH -p debug
#SBATCH -N 1
#SBATCH -n 8
#SBATCH -D /.../.../workingdir 
#SBATCH -J Jobname 
#SBATCH --export=NONE
#SBATCH -t 0:10:00
#SBATCH --mem-per-cpu=1000000
#SBATCH --array=1-16
#SBATCH --nice(=100)

PATH2InputFiles=/...

#srun echo $SLURM_JOBID $SLURM_ARRAY_TASK_ID $SLURM_ARRAY_JOB_ID

mkdir $SLURM_JOBID
cd $SLURM_JOBID
~tsu/bin/my_program $PATH2InputFiles/input_$SLURM_ARRAY_TASK_ID.dat
cd ..

