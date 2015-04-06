OBJS = problema_2.o
CC = g++
DEBUG = -g
CPPFLAGS = -Wall -c $(DEBUG)
LDFLAGS = -Wall $(DEBUG)

ej1: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o problema_2

.SUFFIXES: .cpp

.cpp.o:
	$(CC) $(CPPFLAGS) $<

.PHONY: clean
clean:
	rm *.o problema_2

.PHONY: all
all: problema_2

