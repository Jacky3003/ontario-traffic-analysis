# TODO: add separate builds for serial, MPI, OpenMP, and MPI + OpenMP

# unused flags
PROF = -g -pg
CCSTD = g++

# used flags
CC = mpicxx
CFLAGS = -O3 --std=c++14
LDFLAGS = $(shell nc-config --cflags) $(shell nc-config --libs)
LDFLAGOMP = -fopenmp

CLEAN = rm -f

all: traffic

# compile main module with OpenMP

trafficomp: trafficomp.o mathfunctions.o filemodule.o arrayinitomp.o cliargs.o
	${CC} ${CFLAGS} ${LDFLAGOMP} -o $@ $^ ${LDFLAGS}

trafficomp.o: traffic.cc mathfunctions.h filemodule.h arrayinit.h cliargs.h
	${CC} ${CFLAGS} ${LDFLAGOMP} -c -o $@ $<

# compile other modules with OpenMP

arrayinitomp.o: arrayinit.cc arrayinit.h mathfunctions.h
	${CC} ${CFLAGS} ${LDFLAGOMP} -c -o $@ $<

# compile main module

traffic: traffic.o mathfunctions.o filemodule.o arrayinit.o cliargs.o
	${CC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

traffic.o: traffic.cc mathfunctions.h filemodule.h arrayinit.h cliargs.h
	${CC} ${CFLAGS} -c -o $@ $<

# compile other modules

mathfunctions.o: mathfunctions.cc mathfunctions.h
	${CC} ${CFLAGS} -c -o $@ $<

filemodule.o: filemodule.cc filemodule.h
	${CC} ${CFLAGS} -c -o $@ $<

arrayinit.o: arrayinit.cc arrayinit.h mathfunctions.h
	${CC} ${CFLAGS} -c -o $@ $<

cliargs.o: cliargs.cc cliargs.h
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	${CLEAN} traffic.o trafficomp.o mathfunctions.o filemodule.o arrayinit.o cliargs.o
	${CLEAN} trafficomp.o filemoduleomp.o arrayinitomp.o
	${CLEAN} traffic trafficomp
	${CLEAN} results.nc