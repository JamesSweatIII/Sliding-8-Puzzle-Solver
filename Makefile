CXX	= clang++ 

CXXFLAGS	= -std=c++11 -Wall -g

OFILES	= puzzleSolver.o

doxygen = doxygen

.SUFFIXES: .o .cpp

main:	$(OFILES)
	$(CXX) $(OFILES)

puzzleSolver.o: puzzleSolver.o 

clean:
	-rm -f *.o *~ a.out