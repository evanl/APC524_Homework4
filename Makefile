CXX = g++
CXXFLAGS = -g -Wall -fopenmp -O3
SERIALOBJS = heat_serial.o heat_functions.o
OMPOBJS = heat_omp.o heat_omp_functions.o

all: heat_serial heat_omp heat_mpi

heat_serial: $(SERIALOBJS)
	$(CXX) -o $@ $^

heat_omp: $(OMPOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

heat_mpi: heat_mpi.o heat_mpi_functions.o heat_mpi_functions.h
	mpiCC -g -Wall -O3 -o heat_mpi.o heat_mpi_functions.o

heat_mpi.o: heat_mpi_functions.h heat_mpi.cc
	mpiCC -g -Wall -O3 -c heat_mpi.cc

heat_mpi_functions.o: heat_mpi_functions.h heat_mpi_functions.cc
	mpiCC -g -Wall -O3 -c heat_mpi_functions.cc

clean:
	$(RM) *.o
	$(RM) .depend
	$(RM) *~
	$(RM) ./heat_serial
	$(RM) ./heat_omp
	$(RM) ./heat_mpi

depend:
	$(CXX) -MM $(CXXFLAGS) *.cc > .depend

-include .depend
