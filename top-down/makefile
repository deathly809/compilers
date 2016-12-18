
.PHONY:    all clean

all: base compiler

compiler: compiler.cpp
	g++ -I. --std=c++11 compiler.cpp output/*.o -o compiler

base:
	make -C ast
	make -C lexer
	make -C symtable
	make -C hardware

clean:
	-@rm -fv compiler

nuke: clean
	$(MAKE) -C ast nuke
	$(MAKE) -C symtable nuke
	$(MAKE) -C hardware nuke
	$(MAKE) -C lexer nuke
