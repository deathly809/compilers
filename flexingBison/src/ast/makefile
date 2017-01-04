CC      = gcc
CFLAGS  = -I../ -Wall -g -pedantic 
OBIN    = ../../bin

$(OBIN)/node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c -o $(OBIN)/node.o

test: node.h node.c test.c
	$(CC) $(CFLAGS) node.c test.c -o test

clean:
	-@rm -fv test $(OBIN)/node.o

nuke: clean
