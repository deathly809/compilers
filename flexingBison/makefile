
CC=gcc
CFLAGS=-std=c99 -g -O0 -L.
ODIR=./src

.PHONY: all
.PHONY: bison
.PHONY: flex

all: bison flex main

main:
	make -C src

bison:
	make -C bison_files -o ./src/bison.c

flex:
	make -C flex_files

clean:
	-@rm -fv main

nuke: clean
	make -C bison_files nuke
	make -C flex_files nuke
