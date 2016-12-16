
INCLUDE	= -I../ -I"${PWD}"
GCC		= g++
STD		= -std=c++11
CFLAGS	= -Wall ${STD} -g
CMP		= ${GCC} ${CFLAGS} ${INCLUDE}

ODIR    = ../output

main: 
	make -C ../
	make -C ast
	make -C symtable
	make -C hardware
	${CMP} main.cpp $(ODIR)/*.o objs/*.o -o tests

clean:
	rm -f test 
	make -C ../ clean
	make -C ast clean
	make -C symtable clean
	make -C hardware clean
