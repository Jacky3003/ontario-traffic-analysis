#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --time=12:00:00
#SBATCH --job-name ants-job
#SBATCH --mail-type=FAIL

cd $SLURM_SUBMIT_DIR

echo "| Number of MPI Cores | Number of OMP Cores | Time (Seconds) |"
echo "|-----------|-----------|-----------|"

for t in {1,2,4,8,16,24,32}; do
    mpirun -n $t ./trafficomp
done
