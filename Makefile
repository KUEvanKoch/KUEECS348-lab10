CC=g++
CFLAGS=-c -Wall
OBJECTS= lab.o

all: prog

prog: $(OBJECTS)
	$(CC) $(OBJECTS) -o prog

%.o: %.cpp
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o
