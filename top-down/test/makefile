
INCLUDE	= -I../ -I"${PWD}"
GCC		= g++
STD		= -std=c++11
CFLAGS	= -Wall ${STD} -g
CMP		= ${GCC} ${CFLAGS} ${INCLUDE}
EXEC    = tests

ODIR    = ../output

.PHONY: main
.PHONY: base
.PHONY: ast 
.PHONY: symtable
.PHONY: hardware

main: base ast hardware tests

tests: main.cpp ./objs/*.o $(ODIR)/*.o
	${CMP} main.cpp $(ODIR)/*.o objs/*.o -o tests

base:
	make -C ../

ast:
	make -C ast

hardware:
	make -C hardware

symtable:
	make -C symtable

clean:
	-@rm -vf $(EXEC)

nuke: clean
	make -C ast nuke
	make -C symtable nuke
	make -C hardware nuke
