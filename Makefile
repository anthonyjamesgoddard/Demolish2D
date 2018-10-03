all: source

#For debugging
OPT=-g -Wall
#For optimistaion
#OPT=-O

#All objects (except main) come from cpp and hpp 
%.o:	%.cpp %.hpp
	g++ ${OPT} -c -o $@ $<
#use_vectors relies on objects which rely on headers
source:	source.cpp polygon.o object.o vertex.o sector.o
		g++ ${OPT} -o source source.cpp polygon.o object.o vertex.o sector.o

clean:
	rm -f *.o *~ source
