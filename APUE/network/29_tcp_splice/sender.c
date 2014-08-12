#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include "header.h"

#define CLIENT_PORT ((20001+rand()) % 65536)

int socket_create(void)
{
	int client_fd = 0;
	struct sockaddr_in server_addr,client_addr;
	socklen_t socklen = sizeof(server_addr);

	client_fd = socket(AF_INET, SOCK_STREAM, 0);

	srand(time(NULL));//initialize random generator
	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(CLIENT_PORT);
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_aton("127.0.0.1", &server_addr.sin_addr);
	server_addr.sin_port = htons(SERVER_PORT);
	
	errno = 0;
	if (connect(client_fd, (struct sockaddr*)&server_addr, socklen)){
		perror("CONNECT FAILED !!!!!!");
		close(client_fd);
		exit(1);
	}

	printf("connected to server: IP %s PORT %d\n",
			inet_ntoa(server_addr.sin_addr),
			ntohs(server_addr.sin_port));

	return client_fd;
}

ssize_t do_sendfile(int out_fd, int in_fd, off_t offset, size_t count)
{
	ssize_t bytes_sent;
	size_t total_bytes_sent = 0;
	while (total_bytes_sent < count) {
		int send_size = ((count - total_bytes_sent) > BLOCK_SIZE) ?
				BLOCK_SIZE:count - total_bytes_sent;
		if ((bytes_sent = sendfile(out_fd, in_fd, &offset,
						send_size)) <= 0) {
			if (errno == EINTR || errno == EAGAIN) {
				// Interrupted system call/try again
				// Just skip to the top of the loop and try again
				continue;
			}
			perror("sendfile");
			return -1;
		}
		offset += bytes_sent;
		total_bytes_sent += bytes_sent;
		fprintf(stderr, "send %d bytes so far.\n", total_bytes_sent);
	}
	return total_bytes_sent;
}

int main(void)
{
	struct stat stat;
	int fd,size;
	int client_sock;

	fd=open("./data",O_RDONLY);
	if (fstat(fd, &stat)) {
		perror("fstat\n");
		exit(1);
	}
	size = stat.st_size;
	printf("file size = %d\n", size);

	client_sock = socket_create();
	do_sendfile(client_sock, fd, 0, FILE_SIZE);
	close(client_sock);

	close(fd);

	return 0;
}
