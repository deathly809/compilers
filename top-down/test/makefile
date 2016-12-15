
INCLUDE	= -I../ -I"${PWD}"
GCC		= g++
STD		= -std=c++11
CFLAGS	= -Wall ${STD} -g
CMP		= ${GCC} ${CFLAGS} ${INCLUDE}
ODIR 	= ../output

SOURCES    := ${wildcard *.cpp}
OBJECTS    := ${SOURCES:.cpp=.o}
OBJS       := $(patsubst %,%,$(OBJECTS))

main: ${OBJS} lib.o
	${CMP} $(ODIR)/*.o ./*.o -o main


%.o: %.cpp
	${CMP} -c $< 

debug:
	${CMP} -DDEBUG *.cpp $(ODIR)/*.o -o main

lib.o:
	make -C ../
	

clean:
	rm -f main
	rm *.o
	make -C ../ clean
