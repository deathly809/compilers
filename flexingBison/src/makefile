
CC      = gcc
CFLAGS  = -Wall -g -I.

OBIN    = ../bin

.PHONY: symtable
.PHONY: ast

all: bison flex $(OBIN)/util.o $(OBIN)/common.o $(OBIN)/constants.o symtable ast $(OBIN)/main

bison:
	make -C bison_files

flex:
	make -C flex_files

$(OBIN)/constants.o: constants.h constants.c
	$(CC) $(CFLAGS) -c constants.c -o $(OBIN)/constants.o

$(OBIN)/util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c -o $(OBIN)/util.o

$(OBIN)/common.o:
	$(CC) $(CFLAGS) -c common.c -o $(OBIN)/common.o

symtable:
	make -C symtable

ast:
	make -C ast

$(OBIN)/main: main.c
	$(CC) $(CFLAGS) $(OBIN)/*.o main.c -o $(OBIN)/main

clean:
	-@rm -fv $(OBIN)/main $(OBIN)/common.o $(OBIN)/util.o $(OBIN)/common.o

nuke: clean
	make -C bison_files nuke
	make -C flex_files nuke
	make -C symtable nuke
	make -C ast nuke
