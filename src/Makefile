CC = g++
CFLAGS = -O3 --std=c++14

CLEAN = rm -f

all: traffic

# compile main module

traffic: traffic.o mathfunctions.o output.o
	${CC} ${CFLAGS} -o $@ $^

traffic.o: traffic.cc mathfunctions.h output.h
	${CC} ${CFLAGS} -c -o $@ $<

# compile other modules

mathfunctions.o: mathfunctions.cc mathfunctions.h
	${CC} ${CFLAGS} -c -o $@ $<

output.o: output.cc output.h
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	${CLEAN} traffic.o mathfunctions.o output.o
	${CLEAN} traffic