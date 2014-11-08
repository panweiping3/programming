#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>


#define TIMES 1024*1024*10

int main(int argc, char **argv)
{
	int i;
	int len0, len1;
	char *buf0 = NULL, *buf1 = NULL;
	int client_fd;
	struct sockaddr_in server_addr;
	socklen_t socklen = sizeof(server_addr);

	if (argc < 5) {
		printf("./client IP port first_packet_size second_packet_size\n");
		printf("packet_size <= 8192 \n");
		exit(1);
	}

	client_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
	server_addr.sin_port = htons(atoi(argv[2]));

#if 0
	if (connect(client_fd, (struct sockaddr*)&server_addr, socklen)){
		printf("connect error\n");
		close(client_fd);
		exit(1);
	}
#endif

	printf("connected to server: IP %s PORT %d\n",
			inet_ntoa(server_addr.sin_addr),
			ntohs(server_addr.sin_port));
	
	len0 = atoi(argv[3]);
	buf0 = malloc(len0);
	memset(buf0, 'a', len0);
	len1 = atoi(argv[4]);
	buf1 = malloc(len1);
	memset(buf1, 'b', len1);

	printf("send data start\n");
	errno = 0;
	if (sendto(client_fd, buf0, len0, MSG_FASTOPEN, 
		(struct sockaddr *) &server_addr, socklen) < 0)
		printf("error: %s\n",strerror(errno)); 

	for (i=0; i<10; ++i) {
		if (send(client_fd, buf0, len0, 0) < 0) {
			printf("send buf0 error\n");
			break;
		}
		if (send(client_fd, buf1, len1, 0) < 0) {
			printf("send buf1 error\n");
			break;
		}
	}
	printf("send data end\n");
	close(client_fd);
	return 0;
}
