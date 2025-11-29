# ontario-traffic-analysis

## About this Project

This project aims to give a visualization of traffic density with respect to time and the position of car density on a 1-D road. There are two choices of analysis that is covered here. First, density can be mapped as a set of ordered discrete points from a trigonometric function. Secondly, an attempt is made to model traffic density of Ontario based on [data supplied by Statistics Canada](https://www150.statcan.gc.ca/n1/pub/71-607-x/71-607-x2022018-eng.htm).

## Requirements
The project requires sourcing from the following file found in the ```scripts``` folder after logging on to SciNet's Teach cluster, documentation on the cluster itself can be found [here](https://docs.scinet.utoronto.ca/index.php/Teach).
```bash
$ source teachsetup
```
Code compilation should work after gathering the nessecary libraries on the cluster.

## Compile the Code

First ```cd``` into the source code directory and compile the program:
```bash
$ cd src
$ make all
```

The program can be cleaned and re-compiled as shown below:
```bash
$ make clean
$ make all
```

To run a sample of the program against smooth densities based on the $sin(x)$ function, simply run the program:
```bash
$ ./traffic
```

To run the program based on a preset of densities based on a written ```.data``` file, run the following (if the file is located in the ```src/data``` directory):
```bash
$ ./traffic data/<path-to-file>.data
```
A sample file called ```sample.data``` is in the ```src/data``` directory to give a sample for what format the program expects.

## Extra Documentation:
- Running the profiling for the code: 
- Python scripts documentation: 
- Run the program with data provided by Statistics Canada: