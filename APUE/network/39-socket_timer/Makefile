CC = g++

CFLAGS = -Wall -g 

all:	client main

client: client.o
	$(CC) $(CFLAGS) -o client client.c

server: main.o
	$(CC) $(CFLAGS) -o main main.c

clean:
	rm -f client main *.o

