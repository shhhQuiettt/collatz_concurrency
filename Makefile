CC = gcc
CFLAGS = -Wall -Wextra 

all: program
	
program: ./build/collatz.o
	$(CC) $(CFLAGS) -o collatz ./build/collatz.o

./build/collatz.o: collatz.c
	$(CC) $(CFLAGS) -c collatz.c -o ./build/collatz.o

clean:
	rm -f ./build/*
	rm -f collatz

