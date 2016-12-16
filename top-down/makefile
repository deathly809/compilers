CPP        = g++
CPPFLAGS   = -I./ -std=c++11 -Wall -pedantic -O2 -g -c
ODIR       = ./output

SOURCES    := ${wildcard *.cpp}
OBJECTS    := ${SOURCES:.cpp=.o}
OBJS       := $(patsubst %,$(ODIR)/%,$(OBJECTS))

_EXEC      := testScanner testLexer testParser 
EXEC       := $(patsubst %,$(ODIR)/exec/%,$(_EXEC))

.PHONY:    all clean

.SUFFIXES: .cpp .o

all:       main $(EXEC)
	rm $(ODIR)/test*.o
	mkdir -p $(ODIR)/exec

$(ODIR)/exec/testParser:
	mv $(ODIR)/testParser.o $(ODIR)/exec
	g++ -std=c++11 $(ODIR)/Scanner.o $(ODIR)/Lexer.o $(ODIR)/Lexeme.o $(ODIR)/LexemeTypes.o $(ODIR)/exec/testParser.o $(OUTDIR)/Parser.o -o $(ODIR)/exec/testParser

$(ODIR)/exec/testLexer:
	mv $(ODIR)/testLexer.o $(ODIR)/exec
	g++ -std=c++11 $(ODIR)/Scanner.o $(ODIR)/Lexer.o $(ODIR)/Lexeme.o $(ODIR)/LexemeTypes.o $(ODIR)/exec/testLexer.o -o $(ODIR)/exec/testLexer

$(ODIR)/exec/testScanner:
	mv $(ODIR)/testScanner.o $(ODIR)/exec
	g++ -std=c++11 $(ODIR)/Scanner.o $(ODIR)/Lexeme.o $(ODIR)/LexemeTypes.o $(ODIR)/exec/testScanner.o -o $(ODIR)/exec/testScanner

main:      $(OBJS)
	$(MAKE) -C ast 

$(ODIR)/%.o: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	-rm -fv $(OBJS) 
	$(MAKE) -C ast clean
