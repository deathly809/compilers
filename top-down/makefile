
.PHONY:    all clean

all:
	make -C ast
	make -C lexer
	make -C symtable
	make -C hardware

compiler: compiler.cpp
	g++ -I. --std=c++11 compiler.cpp output/*.o -o compiler


clean:
	$(MAKE) -C ast clean
	$(MAKE) -C symtable clean
	$(MAKE) -C hardware clean
	$(MAKE) -C lexer clean
