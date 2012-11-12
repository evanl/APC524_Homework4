CXX = g++
CXXFLAGS = -g -Wall
OBJECTS =  test_main.o test_functions.o

all: test_main

test_main: $(OBJECTS)
	$(CXX) -o $@ $^

clean:
	$(RM) *.o
	$(RM) .depend
	$(RM) *~
	$(RM) test_main

depend:
	$(CXX) -MM $(CXXFLAGS) *.cc > .depend

-include .depend
