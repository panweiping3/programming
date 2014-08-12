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

#define TEST_ACCEPT 0

#define SERVER_PORT 20000 		// define the defualt connect port id
#define LENGTH_OF_LISTEN_QUEUE 1 	// length of listen queue in server
#define BUFFER_SIZE 255

void *thread(void *client_fd)
{
	char buf[BUFFER_SIZE] = {'\0'};

	bzero(buf, BUFFER_SIZE);
	
	while (1) {
		if (recv((*(int *)client_fd), buf, BUFFER_SIZE, 0) == 0) {
			fprintf(stderr, "client closed ?\n");
			close(*(int *)client_fd);
			break;
		}
	}
	exit(0);
}

int main(int argc, char **argv)
{
	pthread_t thread_id;
	int server_fd,client_fd;
	struct sockaddr_in servaddr;
	struct sockaddr_in client_addr;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);

	bind(server_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(server_fd, LENGTH_OF_LISTEN_QUEUE);

	while (1) {
		socklen_t length = sizeof(client_addr);

		client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &length);
		printf("a client connected: IP %s PORT %d\n",
				inet_ntoa(client_addr.sin_addr),
				ntohs(client_addr.sin_port));	

		if (pthread_create(&thread_id, NULL, thread, (void *)&client_fd) < 0) {
			fprintf(stderr, "create thread error\n");
			exit(1);
		}
	}
	close(server_fd);

	return 0;
}

