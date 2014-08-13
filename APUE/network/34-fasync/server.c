#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#define SERVER_PORT 20000
#define BUFFER_SIZE 255

void *thread_sync(void *client_fd)
{
	char buf[BUFFER_SIZE];

	memset(buf, '\0', BUFFER_SIZE);

	fprintf(stderr, "I am sleeping here to wait for new data\n");
	if (recv((*(int *)client_fd), buf, BUFFER_SIZE, 0) < 0) {
		fprintf(stderr, "get message from client error\n");
		close(*(int *)client_fd);
	}
	printf("%s\n", buf);
	close(*(int *)client_fd);

	return NULL;
}

void data_handler()
{
	printf("data is available !\n");	
	exit(1);
}

int main(int argc, char **argv)
{
	pthread_t thread_id0;
	int server_fd,client_fd;
	struct sockaddr_in servaddr;
	struct sockaddr_in client_addr;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);

	bind(server_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(server_fd, 1);

	while (1) {
		int oflags;
		socklen_t length = sizeof(client_addr);

		client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &length);
		printf("a client connected: IP %s PORT %d\n",
				inet_ntoa(client_addr.sin_addr),
				ntohs(client_addr.sin_port));	

		pthread_create(&thread_id0, NULL, thread_sync, (void *)&client_fd);

		signal(SIGIO, &data_handler);
		fcntl(client_fd, F_SETOWN, getpid());
		oflags = fcntl(client_fd, F_GETFL);
		fcntl(client_fd, F_SETFL, oflags | FASYNC);
	}

	close(server_fd);

	return 0;
}


