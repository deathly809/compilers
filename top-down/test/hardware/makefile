
INCLUDE	= -I../../ 
GCC		= g++
STD		= -std=c++11
CFLAGS	= -Wall ${STD} -g
CMP		= ${GCC} ${CFLAGS} ${INCLUDE}
ODIR 	= ../objs

SOURCES    := ${wildcard *.cpp}
OBJECTS    := ${SOURCES:.cpp=.o}
OBJS       := $(patsubst %,$(ODIR)/%,$(OBJECTS))

main: ${OBJS} 


$(ODIR)/%.o: %.cpp 
	${CMP} -c $< -o $@


clean:
	rm -f ${OBJS}

nuke: clean
