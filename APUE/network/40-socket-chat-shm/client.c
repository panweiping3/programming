#define _GNU_SOURCE 1
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <arpa/inet.h>
#include <assert.h>
#include <poll.h>
#include <fcntl.h>


#define BUFFER_SIZE 64

int main(int argc, char **argv)
{    
	int ret;
	const char *ip;
	int port;
	char read_buf[BUFFER_SIZE];
	int client_fd;
	struct sockaddr_in server_addr;
	struct pollfd fds[2];
	int pipefd[2];
	socklen_t socklen = sizeof(server_addr);

	if (argc <= 2 ) {
		printf("usage: ./client ip_address port_number\n");
		return 1;
	}

	ip = argv[1];
	port = atoi(argv[2]);

	client_fd = socket(AF_INET, SOCK_STREAM, 0);
	assert(client_fd != -1);

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &server_addr.sin_addr);
	server_addr.sin_port = htons(port);
	
	errno = 0;
	if (connect(client_fd, (struct sockaddr*)&server_addr, socklen)){
		perror("CONNECT FAILED !!!!!!");
		close(client_fd);
		exit(1);
	}

	printf("connected to server: IP %s PORT %d\n",
		inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;
	fds[0].revents = 0;
	fds[1].fd = client_fd;
	fds[1].events = POLLIN | POLLRDHUP;
	fds[1].revents = 0;

	ret = pipe(pipefd);
	assert(ret != -1);

	while (1) {
		ret = poll(fds, 2, -1);
		if (ret < 0) {
			printf("poll failure\n");
			break;
		}

		if (fds[1].revents & POLLRDHUP) {
			printf("server close the connection\n");
			break;
		} else if (fds[1].revents & POLLIN) {
			memset(read_buf, '\0', BUFFER_SIZE);
			recv(fds[1].fd, read_buf, BUFFER_SIZE-1, 0);
			printf("%s\n",read_buf);
		}

		if (fds[0].revents & POLLIN) {
			splice(STDIN_FILENO, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
			splice(pipefd[0], NULL, client_fd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
		}
	}

	close(client_fd);

	return 0;
}
