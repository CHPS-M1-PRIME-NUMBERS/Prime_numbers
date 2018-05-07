#!/bin/bash
#@ class            = clallmds+
#@ job_name         = DAMS2MANTES
#@ total_tasks      = 16                         
#@ node             = 1                 
#@ as_limit         = 7gb                        
#@ node_usage       = not_shared                 
#                                                
#@ wall_clock_limit = 02:00:00
#@ output           = $(job_name).$(jobid).log
#@ error            = $(job_name).$(jobid).err
#@ job_type         = mpich
#@ environment      = COPY_ALL 
#@ queue
#

module load gnu-env/5.4.0  openmpi/1.10.0_gnu54 
export OMP_NUM_THREADS=1  
cd build/
mpirun -x OMP_NUM_THREADS -report-bindings ./prime_numbers -k 10 1 10000000

