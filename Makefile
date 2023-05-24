CC = gcc
CFLAGS = -Wall -Wextra 

all: program
	
program: ./build/collatz.o ./build/collatzUtils.o
	$(CC) $(CFLAGS) -o collatz ./build/collatz.o ./build/collatzUtils.o

./build/collatz.o: collatz.c collatzUtils/collatzUtils.h
	$(CC) $(CFLAGS) -c collatz.c -o ./build/collatz.o

./build/collatzUtils.o: collatzUtils/collatzUtils.c collatzUtils/collatzUtils.h
	$(CC) $(CFLAGS) -c collatzUtils/collatzUtils.c -o ./build/collatzUtils.o

clean:
	rm -f ./build/*
	rm -f collatz

