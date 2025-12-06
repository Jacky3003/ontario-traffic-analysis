# Profiling Guide

NOTE: currently the code profiling will only be supported on the ```serial``` branch of this project. This guide assumes that you are using this branch as a baseline for code profiling.

By performing the profiling on the code in ```src```, it will motivate the key areas in where MPI and OpenMP can make a difference.

## Time Profiling

First, make sure to add ```-g -pg``` as options in the Makefile, located in ```src/Makefile```:
```Makefile
CC = g++
CFLAGS = -O3 -g -pg --std=c++14 # <-- add options flags here.
LDFLAGS = -lnetcdf
```

We can now compile the program with ```make``` and running the program with ```./traffic``` as needed. After this process, you should see a file called ```gmon.out```. Using this file, we can provide a breakdown for how our program ran via ```gprof``` (if no time is captured, consider increasing the problem space):

```bash
$ gprof traffic gmon.out > runtime_profiling.txt
```

## Memory Profiling

Memory profiling is done with a tool called ```massif```. It is a tool used in the valgrind ecosystem to check on the heap memory usage of a program. The offical docs can be found here: https://valgrind.org/docs/manual/ms-manual.html

To memory profile wiht Massif, add ```--tool=massif``` on a valgrind command and run it.
```
$ valgrind --tool=massif --time-unit=B ./traffic
```
The ```--time-unit=B``` command specifies to use the number of bytes allocated/dealocated on the heap and stack(s) as a basis of time for the graph.

The command will output a file called ```massif.out.<pid>```, where ```pid``` is the process id. The following will show the information gathered:
```bash
$ ms_print massif.out.<pid> > memory_profile.txt
```