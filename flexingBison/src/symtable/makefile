
CC      = gcc
CFLAGS  = -Wall -g -pedantic -I../
OBIN    = ../../bin

$(OBIN)/symtable.o: symtable.c symtable.h
	$(CC) $(CFLAGS) -c symtable.c -o $(OBIN)/symtable.o

test: ../constants.h symtable.c symtable.h test.c
	gcc -I../ -Wall -g constants.c symtable.c test.c -o test

clean:
	-@rm -fv test $(OBIN)/symtable.o

nuke: clean
