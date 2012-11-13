CXX = g++
CXXFLAGS = -g -Wall
TESTOBJECTS =  test_main.o test_functions.o
SERIALOBJS = heat_serial.o heat_functions.o

all: test_main heat_serial

test_main: $(TESTOBJECTS)
	$(CXX) -o $@ $^

heat_serial: $(SERIALOBJS)
	$(CXX) -o $@ $^

clean:
	$(RM) *.o
	$(RM) .depend
	$(RM) *~
	$(RM) test_main

depend:
	$(CXX) -MM $(CXXFLAGS) *.cc > .depend

-include .depend
