

CC      = gcc
CFLAGS  = -I../ -Wall -g -c
OBIN    = ../../bin

$(OBIN)/grammar.tab.o: grammar.tab.c
	$(CC) $(CFLAGS) grammar.tab.c -o $(OBIN)/grammar.tab.o

grammar.tab.c: grammar.y
	bison -Wall -v -d grammar.y

clean:
	-@rm -fv grammar.tab.c grammar.tab.h $(OBIN)/grammar.tab.o *.output

nuke: clean
