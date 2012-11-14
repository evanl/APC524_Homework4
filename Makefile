CXX = g++
CXXFLAGS = -g -Wall
SERIALOBJS = heat_serial.o heat_functions.o

all: heat_serial 

heat_serial: $(SERIALOBJS)
	$(CXX) -o $@ $^


clean:
	$(RM) *.o
	$(RM) .depend
	$(RM) *~
	$(RM) ./heat_serial
	$(RM) ./heat_omp

depend:
	$(CXX) -MM $(CXXFLAGS) *.cc > .depend

-include .depend
