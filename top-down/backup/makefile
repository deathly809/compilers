CPP        = g++
CPPFLAGS   = -I../ -std=c++11 -Wall -pedantic -O2 -g
ODIR       = ../output

EXEC       := ${wildcard *.cpp}
OBJS    := ${EXEC:.cpp=.out}

.PHONY:    all clean

.SUFFIXES: .cpp .o

all: main

main:      $(OBJS)

%.out: %.cpp
	$(CPP) $(CPPFLAGS) $(ODIR)/*.o $< -o $@

clean:
	rm -fv $(OBJS) 

nuke: clean
