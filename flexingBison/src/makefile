
CC      = gcc
CFLAGS  = -Wall -g -I.

OBIN    = ../bin

all: bison flex $(OBIN)/util.o symtable ast $(OBIN)/main

bison:
	make -C bison_files

flex:
	make -C flex_files

$(OBIN)/util.o:
	$(CC) $(CFLAGS) -c util.c -o $(OBIN)/util.o

symtable:
	make -C symtable

ast:
	make -C ast

$(OBIN)/main:
	$(CC) $(CFLAGS) $(OBIN)/*.o main.c -o $(OBIN)/main

clean:
	-@rm -fv $(OBIN)/main

nuke: clean
	make -C bison_files nuke
	make -C flex_files nuke
	make -C symtable nuke
	make -C ast nuke
