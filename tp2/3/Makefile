NUM=$(notdir $(shell pwd))
EXEC=$(NUM)
OBJS = $(EXEC).o
CC = g++
DEBUG = -g
DEFINES= -DNO_JUEZ 
CPPFLAGS = -Wall $(DEBUG) $(DEFINES) -std=c++11
LDFLAGS = -Wall $(DEBUG)

$(EXEC): clean $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXEC)

.SUFFIXES: .cpp

.cpp.o:
	$(CC) $(CPPFLAGS) -c $<

.PHONY: clean medir
clean:
	rm -f *.o $(EXEC)

medir: clean
	$(CC) $(CPPFLAGS) -DMEDIR $(EXEC).cpp -o $(EXEC)

.PHONY: all
all: $(EXEC)

