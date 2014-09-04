CC = gcc

CFLAGS = -Wall -g 

all:	client server

client: client.o
	$(CC) $(CFLAGS) -o client client.c

server: server.o
	$(CC) $(CFLAGS) -o server server.c -lpthread

clean:
	rm -f client server *.o

