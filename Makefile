CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: program reader test
	

program: ./build/collatz.o ./build/collatzUtils.o ./build/sharedMemory.o
	$(CC) $(CFLAGS) -o collatz ./build/collatz.o ./build/collatzUtils.o ./build/sharedMemory.o

./build/collatz.o: collatz.c lib/collatzUtils.h lib/sharedMemory.h
	$(CC) $(CFLAGS) -c collatz.c -o ./build/collatz.o

./build/collatzUtils.o: lib/collatzUtils.c lib/collatzUtils.h 
	$(CC) $(CFLAGS) -c lib/collatzUtils.c -o ./build/collatzUtils.o

./build/sharedMemory.o: lib/sharedMemory.c lib/sharedMemory.h
	$(CC) $(CFLAGS) -c lib/sharedMemory.c -o ./build/sharedMemory.o

########

reader: ./build/reader.o  ./build/sharedMemory.o
	$(CC) $(CFLAGS) -o reader ./build/reader.o  ./build/sharedMemory.o

./build/reader.o: reader.c lib/sharedMemory.h
	$(CC) $(CFLAGS) -c reader.c -o ./build/reader.o

########

test: ./build/test.o
	$(CC) $(CFLAGS) -o test ./build/test.o

./build/test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o ./build/test.o

clean:
	rm -f collatz
	rm -f reader
	rm -f test

