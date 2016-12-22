
CC      = g++
CFLAGS  = -I. -std=c++11 -g -O0 

all: lex.yy.o

lex.yy.o: lex.yy.c
	$(CC) -c $(CFLAGS) lex.yy.c

lex.yy.c: tokens.l
	lex tokens.l


clean:
	-@rm -fv lex.yy.c lex

nuke: clean
