
CC      = g++
CFLAGS  = -I../ -std=c++11 -g -O0 
ODIR    = ../../bin

all: $(ODIR)/lex.yy.o

$(ODIR)/lex.yy.o: lex.yy.c
	$(CC) -c $(CFLAGS) lex.yy.c -o $(ODIR)/lex.yy.o

lex.yy.c: tokens.l
	flex tokens.l


clean:
	-@rm -fv lex.yy.c $(ODIR)/lex.yy.o 

nuke: clean
