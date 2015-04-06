OBJS = problema_1.o
CC = g++
DEBUG = -g
CPPFLAGS = -Wall -c $(DEBUG)
LDFLAGS = -Wall $(DEBUG)

ej1: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o problema_1

.SUFFIXES: .cpp

.cpp.o:
	$(CC) $(CPPFLAGS) $<

.PHONY: clean
clean:
	rm *.o problema_1

.PHONY: all
all: problema_1

