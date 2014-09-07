#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/syscall.h>

#define SERVER_PORT 20000 		// define the defualt connect port id
#define LENGTH_OF_LISTEN_QUEUE 10 	// length of listen queue in server
#define BUFFER_SIZE 255
#define THREAD_NUM 10

pthread_t thread_array[THREAD_NUM];
int thread_hit[THREAD_NUM];

void *thread(void *data)
{
	pthread_t tid = pthread_self();

	char buf[BUFFER_SIZE] = {'\0'};

	int server_fd;
	struct sockaddr_in servaddr;
	struct sockaddr_in client_addr;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);

	int optval = 1;
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

	bind(server_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(server_fd, LENGTH_OF_LISTEN_QUEUE);

	while (1) {
		socklen_t length = sizeof(client_addr);
		int client_fd = -1;
		int i;

		client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &length);
		printf("thread %lu a client connected: IP %s PORT %d\n",
				tid,
				inet_ntoa(client_addr.sin_addr),
				ntohs(client_addr.sin_port));	

		if (client_fd != -1) {
			bzero(buf, BUFFER_SIZE);

			int ret = recv(client_fd, buf, BUFFER_SIZE, 0);
			buf[ret-1] = '\0';
			fprintf(stderr, "thread %lu get data %s\n", tid, buf);
			close(client_fd);
		}

		for (i=0; i< THREAD_NUM; ++i)
			if (thread_array[i] == tid)
				thread_hit[i]++;
	}

	close(server_fd);
	return NULL;
}

void haha()
{
	int i;
	for (i=0; i<THREAD_NUM; ++i)
		printf("thread %lu hit %d\n", thread_array[i], thread_hit[i]);
	exit(0);
}

int main(int argc, char **argv)
{
	int i;
	pthread_t thread_id;

	signal(SIGINT, haha);

	for (i=0; i<THREAD_NUM; ++i) {
		if (pthread_create(&thread_id, NULL, thread, NULL) < 0) {
			fprintf(stderr, "create thread error\n");
			exit(1);
		}
		thread_array[i] = thread_id;
		thread_hit[i] = 0;
	}

	for (i=0; i<THREAD_NUM; ++i) {
		pthread_join(thread_array[i], NULL);
	}
	return 0;
}


