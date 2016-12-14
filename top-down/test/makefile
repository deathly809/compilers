
INCLUDE	= -I../ -I"${PWD}"
GCC		= g++
STD		= -std=c++11
CFLAGS	= -Wall ${STD} -g
CMP		= ${GCC} ${CFLAGS} ${INCLUDE}
ODIR 	= ../output

main: *.cpp lib.o
	${CMP} *.cpp $(ODIR)/*.o -o main
	./main

lib.o:
	make -C ../ast

	

clean:
	rm -f main
