CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: program
	
program: ./build/collatz.o ./build/collatzUtils.o ./build/sharedMemory.o
	$(CC) $(CFLAGS) -o collatz ./build/collatz.o ./build/collatzUtils.o ./build/sharedMemory.o

./build/collatz.o: collatz.c lib/collatzUtils.h lib/sharedMemory.h
	$(CC) $(CFLAGS) -c collatz.c -o ./build/collatz.o

./build/collatzUtils.o: lib/collatzUtils.c lib/collatzUtils.h 
	$(CC) $(CFLAGS) -c lib/collatzUtils.c -o ./build/collatzUtils.o

./build/sharedMemory.o: lib/sharedMemory.c lib/sharedMemory.h
	$(CC) $(CFLAGS) -c lib/sharedMemory.c -o ./build/sharedMemory.o

clean:
	rm -f collatz

