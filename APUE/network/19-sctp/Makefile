CC = gcc

CFLAGS = -Wall -g 

all:	client server

client: client.o
	$(CC) $(CFLAGS) -o client client.c -L/usr/local/lib -lsctp

server: server.o
	$(CC) $(CFLAGS) -o server server.c -L/usr/local/lib -lsctp

clean:
	rm -f client server *.o

