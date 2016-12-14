CPP        = g++
CPPFLAGS   = -I./ -std=c++11 -Wall -pedantic -O2 -g -c
ODIR       = ./output

SOURCES    := ${wildcard *.cpp}
OBJECTS    := ${SOURCES:.cpp=.o}
OBJS       := $(patsubst %,$(ODIR)/%,$(OBJECTS))

_EXEC      := testScanner testLexer
EXEC       := $(patsubst %,$(ODIR)/%,$(_EXEC))

.PHONY:    all clean

.SUFFIXES: .cpp .o

all:       main $(EXEC) main
	echo "Hello"
	mkdir -p $(ODIR)/exec
	mv $(ODIR)/test* $(ODIR)/exec/

$(ODIR)/testParser:
	g++ -std=c++11 $(ODIR)/Scanner.o $(ODIR)/Lexer.o $(ODIR)/Lexeme.o $(ODIR)/LexemeTypes.o $(ODIR)/testParser.o $(OUTDIR)/Parser.o -o $(ODIR)/testParser

$(ODIR)/testLexer:
	g++ -std=c++11 $(ODIR)/Scanner.o $(ODIR)/Lexer.o $(ODIR)/Lexeme.o $(ODIR)/LexemeTypes.o $(ODIR)/testLexer.o -o $(ODIR)/testLexer

$(ODIR)/testScanner:
	g++ -std=c++11 $(ODIR)/Scanner.o $(ODIR)/Lexeme.o $(ODIR)/LexemeTypes.o $(ODIR)/testScanner.o -o $(ODIR)/testScanner

main:      $(OBJS)
	echo "main"
	$(MAKE) -C ast 

$(ODIR)/%.o: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	-rm -fv $(OBJS) 
	$(MAKE) -C ast clean
