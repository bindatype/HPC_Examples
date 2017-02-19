#!/bin/bash

# set output and error output filenames, %j will be replaced by Slurm with the jobid
#SBATCH -o testing%j.out
#SBATCH -e testing%j.err 

# single node in the "short" partition
#SBATCH -N 1
#SBATCH -p short

# half hour timelimit
#SBATCH -t 0:30:00

module load mathematica
ssh login4 -L 16286:161.253.28.147:16286 -N &

# test.m is your mathematica code
math -script test.m
