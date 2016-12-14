CPP        = g++
CPPFLAGS   = -I../../ -std=c++11 -Wall -pedantic -O2 -g -c
ODIR       = ../../output

SOURCES    := ${wildcard *.cpp}
OBJECTS    := ${SOURCES:.cpp=.o}
OBJS       := $(patsubst %,$(ODIR)/%,$(OBJECTS))

.PHONY:    all clean

.SUFFIXES: .cpp .o

all:       main

main:      $(OBJS)

$(ODIR)/%.o: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	-rm -fv $(OBJS) 
