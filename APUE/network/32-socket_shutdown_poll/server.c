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
	struct pollfd pollfds;
	int timeout;  

	timeout = 5000;  
	pollfds.fd = *(int *)client_fd;                //设置监控sockfd  
	pollfds.events = POLLRDHUP;            //设置监控的事件  

	switch(poll(&pollfds, 1, timeout))
	{       //开始监控  
		case -1:                    //函数调用出错  
			printf("poll error \n");  
			break;  
		case 0:  
			printf("time out \n");  
			break;  
		default:                    //得到数据返回  
			printf("sockfd have some event\n");  
		 	printf("event value is 0x%x\n",pollfds.revents);  
			break;  
	} 
	if (POLLRDHUP == pollfds.revents) {
		printf("client shutdown\n");  
		close(*(int *)client_fd);
		exit(0);
	}

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


