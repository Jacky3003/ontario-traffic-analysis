# How to Run Sample Data From Statistics Canada

## Getting the Data

Below is a step by step guide to get data from Statistics Canada containing information on traffic flow:

1. Go to https://www150.statcan.gc.ca/n1/pub/71-607-x/71-607-x2022018-eng.htm
2. Scroll down to the "Data" section and download the given CSV file. As of the time this is being written, the reported file size should be 14264 KB.
3. Move the CSV file into this repository. In particular, create a directory called ```scripts/data``` for the downloaded CSV to be stored.

## How the Program Works

The sample script ```ont_traffic_processor.py``` will process the amount of starting cars on Steeles Avenue in Ontario, based on the data captured by Statistics Canada. Each intersection will act as a critical point, and based on the amount of cars between two neighbouring critical points, the falloff or increase in traffic will be 1 percent of the current value. For example, consider the following as critical values:

```bash
200 -> 100 -> 150
```
So to get from the first critical point to the second, we generate the following intermediate values:
```bash
200 -> 198 -> 196 -> ... -> 102 -> 100
```
And a similar result happens when going from 100 to 150, now in the increasing direction. See the sample script for more implementation details if needed. 

## Running the Program Alongside the Analysis

On the Teach cluster, be sure to run ```source teachsetup```, then run the following:

```bash
python3 ont_traffic_processor.py
```
The script itself will show the inital plot of how the traffic is stationed along the road.

The ```.data``` file should then be located in the ```scripts/data``` directory, move this file into the same directory as the compiled program, and run the program similar to the following format (assuming the ```.data``` file is called ```traffic_density.data```):

```bash
mpirun -n 1 -x OMP_NUM_THREADS=1 ./trafficomp -f data/traffic_density.data -io
```