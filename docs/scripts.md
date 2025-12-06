# Scripts Guide

## Running the Python Scripts for Visualization

Before running the scripts, be sure to run ```source teachsetup``` on the Teach cluster to set the environment up (a sample script for module loading is provided in the ```scripts``` directory).

Then we can run the scripts using the following, ensuring that a file called ```results.nc``` is located in a directory called ```scripts/data```:
```bash
$ python3 densities_mesh.py
$ python3 densities_plot.py
```
Then, two ```.png``` files called ```densities_mesh.png``` and ```densities_plot.png``` should be created and can be viewed using any image viewer supporting ```.png```. Additionally, ```densities_mesh.py``` has an interactive 3D mesh to play around with before the program closes as specified by the following Python code:

```python
plt.show()
```

To turn this functionality off, simply comment the line out of the script.

## Running the Scaling Analysis

The scripts are expected to be in the same directory in where the program is compiled. Before running the submission scripts on the Teach cluster, be sure to compile the program:

```bash
make clean; make trafficomp
```

Then we can run ```sbatch``` on each of the scripts, ```mpi-strong.sh``` will be used as an example.

```bash
sbatch mpi-strong.sh
```

To see the output of the submission script, check the output log in the same directory:

```bash
cat slurm-<jobid>.out
```

The output is formatted in a markdown table format, in which the table can be customized to fit a particular analysis (for example converting markdown tables to CSV using an online)