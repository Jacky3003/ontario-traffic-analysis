# TODO: add separate builds for serial, MPI, OpenMP, and MPI + OpenMP

# unused flags
PROF = -g -pg
CCSTD = g++
LDFLAGOMP = -fopenmp

# used flags
CC = mpicxx
CFLAGS = -O3 --std=c++14
LDFLAGS = -lnetcdf

CLEAN = rm -f

all: traffic

# compile main module

traffic: traffic.o mathfunctions.o filemodule.o arrayinit.o
	${CC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

traffic.o: traffic.cc mathfunctions.h filemodule.h arrayinit.h
	${CC} ${CFLAGS} -c -o $@ $<

# compile other modules

mathfunctions.o: mathfunctions.cc mathfunctions.h
	${CC} ${CFLAGS} -c -o $@ $<

filemodule.o: filemodule.cc filemodule.h
	${CC} ${CFLAGS} -c -o $@ $<

arrayinit.o: arrayinit.cc arrayinit.h mathfunctions.h
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	${CLEAN} traffic.o mathfunctions.o filemodule.o arrayinit.o
	${CLEAN} traffic
	${CLEAN} results.nc