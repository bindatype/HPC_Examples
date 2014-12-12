#!/bin/bash 

module load R
Rscript test.R ${SLURM_JOBID} ${SLURM_PROCID}
