#ifndef _GNU_SOURCE
#define _GNU_SOURCE 

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

int socket_create(void)
{
	int server_fd = 0;
	struct sockaddr_in server_addr, client_addr;
	socklen_t socklen = sizeof(server_addr);

	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);

	bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	listen(server_fd, 5);

	server_fd = accept(server_fd, (struct sockaddr *)&client_addr, &socklen);

	return server_fd;
}

ssize_t do_recvfile(int out_fd, int in_fd, loff_t offset, size_t count)
{
	ssize_t bytes, bytes_recive, bytes_in_pipe;
	size_t total_bytes_receive = 0;
	int pipe_fd[2];

	if(pipe(pipe_fd)<0) {
		printf("pipe create error\n");
		return -1;
	}

	// Splice the data from in_fd into the pipe
	while (total_bytes_receive < count) {
		int receive_size = ((count - total_bytes_receive)) >
				BLOCK_SIZE ? BLOCK_SIZE:count-total_bytes_receive;
		if ((bytes_recive = splice(in_fd, NULL, pipe_fd[1], NULL,
					receive_size, SPLICE_F_MORE | SPLICE_F_MOVE)) <= 0) {
			if (errno == EINTR || errno == EAGAIN) {
				// Interrupted system call/try again
				// Just skip to the top of the loop and try again
				continue;
			}
			perror("splice");
			return -1;
		}

		// Splice the data from the pipe into out_fd
		bytes_in_pipe = bytes_recive;
		while (bytes_in_pipe > 0) {
			if ((bytes = splice(pipe_fd[0], NULL, out_fd, &offset, bytes_in_pipe,
							SPLICE_F_MORE | SPLICE_F_MOVE)) <= 0) {
				if (errno == EINTR || errno == EAGAIN) {
					// Interrupted system call/try again
					// Just skip to the top of the loop and try again
					continue;
				}
				perror("splice");
				return -1;
			}
			bytes_in_pipe -= bytes;
		}
		offset += bytes_recive;
		total_bytes_receive += bytes_recive;
		fprintf(stderr, "recieve %d bytes so far.\n", total_bytes_receive);
	}
	return total_bytes_receive;
}

int main(void)
{
	int fd,size;
	int server_sock;

	fd=open("./new_data", O_WRONLY | O_CREAT, 0644);

	server_sock = socket_create();
	do_recvfile(fd, server_sock, 0, FILE_SIZE);

	close(server_sock);
	close(fd);
}

#endif
