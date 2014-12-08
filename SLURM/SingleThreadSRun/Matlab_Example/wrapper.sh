#!/bin/bash 

# ./single_srun $SLURM_PROCID $SLURM_NTASKS  
module load matlab
ssh login4 -L 27000:128.164.84.113:27000 -L 27001:128.164.84.113:27001 -N &
export LM_LICENSE_FILE="27000@localhost"

matlab -nosplash -nodisplay -r "matlab_test($SLURM_PROCID)" -logfile matlab-log-${SLURM_JOBID}_${SLURM_PROCID}.tmp
