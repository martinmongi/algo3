OBJS = ej1.o
CC = g++
DEBUG = -g
CPPFLAGS = -Wall -c $(DEBUG)
LDFLAGS = -Wall $(DEBUG)

ej1: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o ej1

.SUFFIXES: .cpp

.cpp.o:
	$(CC) $(CPPFLAGS) $<

.PHONY: clean
clean:
	rm *.o ej1

.PHONY: all
all: ej1

