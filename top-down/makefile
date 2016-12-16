
.PHONY:    all clean

all:
	make -C ast
	make -C lexer
	make -C symtable
	make -C hardware


clean:
	$(MAKE) -C ast clean
	$(MAKE) -C symtable clean
	$(MAKE) -C hardware clean
	$(MAKE) -C lexer clean
