#define _GNU_SOURCE

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
#include <poll.h>

#define TEST_ACCEPT 0

#define SERVER_PORT 20000 		// define the defualt connect port id
#define LENGTH_OF_LISTEN_QUEUE 1 	// length of listen queue in server
#define BUFFER_SIZE 255

void *thread(void *client_fd)
{
	fd_set rfds;
	struct timeval tv;
	int retval;

	/* Watch stdin (fd 0) to see when it has input. */
	FD_ZERO(&rfds);
	FD_SET(0, &rfds);

	/* Wait * up * to * five * seconds.  * */
	tv.tv_sec = 25;
	tv.tv_usec = 0;

	// WHY we set write fd here ?
	retval = select(1, &rfds, &rfds, NULL, &tv);

	if (retval == -1)
		perror("select()");
	else if (retval) {
		printf("Data is available now.\n");
		printf("client shutdown\n");  
	} else
		printf("No data within 25 seconds.\n");


	close(*(int *)client_fd);
	exit(0);

	return NULL;
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


