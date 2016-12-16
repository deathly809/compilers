
INCLUDE	= -I../ -I"${PWD}"
GCC		= g++
STD		= -std=c++11
CFLAGS	= -Wall ${STD} -g
CMP		= ${GCC} ${CFLAGS} ${INCLUDE}
ODIR 	= ../output

SOURCES    := ${wildcard *.cpp}
OBJECTS    := ${SOURCES:.cpp=.o}
OBJS       := $(patsubst %,objs/%,$(OBJECTS))

main: ${OBJS} lib.o
	${CMP} $(ODIR)/*.o objs/*.o -o main


objs/%.o: %.cpp
	${CMP} -c $< -o $@

debug:
	${CMP} -DDEBUG *.cpp $(ODIR)/*.o -o main

lib.o:
	make -C ../
	

clean:
	rm -f main
	rm -f objs/*.o
	make -C ../ clean
