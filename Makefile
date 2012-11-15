CXX = g++
CXXFLAGS = -g -Wall -fopenmp
SERIALOBJS = heat_serial.o heat_functions.o
OMPOBJS = heat_omp.o heat_omp_functions.o

all: heat_serial heat_omp

heat_serial: $(SERIALOBJS)
	$(CXX) -o $@ $^

heat_omp: $(OMPOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) *.o
	$(RM) .depend
	$(RM) *~
	$(RM) ./heat_serial
	$(RM) ./heat_omp

depend:
	$(CXX) -MM $(CXXFLAGS) *.cc > .depend

-include .depend
