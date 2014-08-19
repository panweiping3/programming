CC = gcc

CFLAGS = -Wall -g 

socket_epoll:socket_epoll.o
	$(CC) -DEPOLL_IT $(CFLAGS) -o socket_epoll socket_epoll.c -lpthread

clean:
	rm -f socket_epoll *.o

