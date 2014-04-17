/**

 * Tcp Server program, It is a simple example only.

 * zhengsh 200520602061 2

 * when client connect to server, send a welcome message and timestamp in server.

 */

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <linux/if.h>
#include <errno.h>

#define SERVER_PORT 20000 // define the defualt connect port id
#define LENGTH_OF_LISTEN_QUEUE 10 //length of listen queue in server
#define BUFFER_SIZE 255
#define WELCOME_MESSAGE "welcome to connect the server. "
void *thread(void *client_fd)
{
	char buf[BUFFER_SIZE] = {'\0'};
	long timestamp;
	int i = 0;
	while (1)
	{	
		bzero(buf, BUFFER_SIZE);
			 
		send((*(int *)client_fd), buf, BUFFER_SIZE, 0);

		i++;
		sleep(1);
		if (i == 10) {
			close (*(int *)client_fd);
			i = 10/2;
		}
	}	
}

int main(int argc, char **argv)
{
	pthread_t thread_id;
	int server_fd,client_fd;
	struct sockaddr_in servaddr;
	struct sockaddr_in client_addr;
	struct ifreq interface;
	socklen_t ifreq_len = sizeof(interface);
	int index;

	if (argc != 2) {
		printf("./a.out interface_name\n");
		exit(1);
	}
	strncpy(interface.ifr_name, argv[1], IFNAMSIZ);

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		// IPv4 TCP connecttion
		printf("create socket error!\n");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);

	if (bind(server_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("bind to port %d failure!\n",SERVER_PORT);
		exit(1);
	}

#if 0
	if (setsockopt(server_fd, SOL_SOCKET, SO_BINDTODEVICE,(char *)&interface, sizeof(interface)) < 0) {
		close(server_fd);
		printf("setsockopt SO_BINDTODEVICE error!\n");
		return -1;
	}
	errno = 0;
	if ((index = getsockopt(server_fd, SOL_SOCKET, SO_BINDTODEVICE, (char *)&interface, &ifreq_len)) < 0) {
		close(server_fd);
		perror("getsockopt SO_BINDTODEVICE error!\n");
		printf("interface index=%d\n", index);
		return -1;
	}
	printf("interface index=%d\n", index);
#endif

	if (listen(server_fd, LENGTH_OF_LISTEN_QUEUE) < 0)
	{
		printf("call listen failure!\n");
		exit(1);
	}

	printf("server is listening....\n");

	while (1)
	{
		char buf[BUFFER_SIZE] = {'\0'};
		long timestamp;
		socklen_t length = sizeof(client_addr);

		client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &length);
		if (client_fd < 0)
		{
			printf("error comes when call accept!\n");
			break;
		}
		else	
		{
			printf("a client connected: IP %s PORT %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));	
		}

		if (pthread_create(&thread_id, NULL, thread, (void *)&client_fd) < 0)
		{
			fprintf(stderr, "create thread error\n");
			exit(1);
		}
	}

	close(server_fd);

	return 0;
}


