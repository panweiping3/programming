#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/tcp.h>

#define BUFFER_SIZE 8192

int main(int argc, char **argv)
{
	int ret = 0;
	int server_fd, client_fd;
	char buf[BUFFER_SIZE];
	struct sockaddr_in servaddr;
	struct sockaddr_in client_addr;

	if (argc < 3) {
		printf("./server IP port \n");
		exit(1);
	}

	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	servaddr.sin_port = htons(atoi(argv[2]));

	ret = bind(server_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if (ret)
		perror("bind error\n");
	else
		printf("bind success \n");

	int qlen = 5;
	setsockopt(server_fd, IPPROTO_TCP, TCP_FASTOPEN, &qlen, sizeof(qlen)); 

	ret = listen(server_fd, 5);
	if (ret)
		perror("listen error\n");
	else
		printf("listening success \n");

	while (1) {
		socklen_t length = sizeof(client_addr);

		client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &length);
		printf("a client connected: IP %s PORT %d\n",
				inet_ntoa(client_addr.sin_addr),
				ntohs(client_addr.sin_port));	
		while (1) {
			memset(buf, '\0', BUFFER_SIZE);
			if (recv(client_fd, buf, BUFFER_SIZE, 0) <= 0) {
				fprintf(stderr, "get message from client error\n");
				close(client_fd);
				break;
			}

			printf("receive data from client:%s\n", buf);
		}

		break;
	}

	close(server_fd);

	return 0;
}


