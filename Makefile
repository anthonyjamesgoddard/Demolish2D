all: source

OPT=-g -Wall

LINKS= -lglut -lGL -lGLU

#All objects (except main) come from cpp and hpp 
%.o:	%.cpp %.hpp
	g++ ${OPT} -c -o $@ $<
#use_vectors relies on objects which rely on headers
source:	source.cpp polygon.o object.o vertex.o sector.o scenario.o render.o collisionpair.o matrix.o
		g++ ${OPT} -o source source.cpp polygon.o object.o vertex.o sector.o scenario.o render.o collisionpair.o matrix.o $(LINKS)

clean:
	rm -f *.o *~ source
