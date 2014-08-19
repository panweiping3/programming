#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <stdbool.h> 

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

int setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);	
	int new_ootion = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_ootion);

	return old_option;
}

void epoll_addfd(int epollfd, int fd, bool enable_et)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN;

	if (enable_et)
		event.events |= EPOLLET;
	
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
}

void epoll_it(struct epoll_event *events, int number, int epollfd, int listenfd)
{
	int i;
	int ret;
	char buf[BUFFER_SIZE];
	for (i=0; i<number; ++i) {
		int sock_fd = events[i].data.fd;

		if (sock_fd == listenfd) {
			int connfd;
			struct sockaddr_in client_address;
			socklen_t client_addrlen = sizeof(struct sockaddr_in);
			connfd = accept(listenfd, (struct sockaddr *)&client_address, &client_addrlen);
			epoll_addfd(epollfd, connfd, false);
		} else if (events[i].events & EPOLLIN) {
			printf("event trigger once\n");
			memset(buf, '\0', BUFFER_SIZE);
			ret = recv(sock_fd, buf, BUFFER_SIZE-1, 0);
			if (ret<=0) {
				close(sock_fd);
				continue;
			}
			printf("get %d bytes of content:%s\n", ret, buf);
		} else
			printf("something else happened.\n");

	}
}

void epoll_et(struct epoll_event *events, int number, int epollfd, int listenfd)
{
	int i;
	int ret;
	char buf[BUFFER_SIZE];
	for (i=0; i<number; ++i) {
		int sock_fd = events[i].data.fd;

		if (sock_fd == listenfd) {
			int connfd;
			struct sockaddr_in client_address;
			socklen_t client_addrlen = sizeof(struct sockaddr_in);
			connfd = accept(listenfd, (struct sockaddr *)&client_address, &client_addrlen);
			epoll_addfd(epollfd, connfd, true);
		} else if (events[i].events & EPOLLIN) {
			printf("event trigger once\n");
			while (1) {
				memset(buf, '\0', BUFFER_SIZE);
				ret = recv(sock_fd, buf, BUFFER_SIZE-1, 0);
				if (ret < 0) {
					if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
						printf("read later\n");
						break;
					}
					close(sock_fd);
					break;
				} else if (ret == 0)
					close(sock_fd);
				else
					printf("get %d bytes of content:%s\n", ret, buf);
			}
		}
	}
}

void epoll_do(struct epoll_event *events, int number, int epollfd, int listenfd)
{	
	#ifdef EPOLL_IT
		epoll_it(events, number, epollfd, listenfd);
	#endif

	#ifdef EPOLL_ET
		epoll_et(events, number, epollfd, listenfd);
	#endif
}

int main(int argc, char *argv[])
{
	char *ip;
	int port;
	int ret;
	struct sockaddr_in address;
	int listenfd, epollfd;
	struct epoll_event events[MAX_EVENT_NUMBER];

	if (argc <= 2) {
		printf("usage:./main ip_address port_number\n");
		return 1;
	}

	ip = argv[1];
	port = atoi(argv[2]);
	bzero(&address, sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, ip, &address.sin_addr);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(listenfd >= 0);

	ret = bind(listenfd, (struct sockaddr *)&address, sizeof(struct sockaddr_in));
	assert(ret != -1);

	ret = listen(listenfd, 5);
	assert(ret != -1);

	epollfd = epoll_create(5);
	assert(epollfd != -1);
	epoll_addfd(epollfd, listenfd, true);

	printf("epoll wait\n");
	while (1) {
		int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
		if (ret < 0) {
			printf("epoll failure\n");
			break;
		}
		
		epoll_do(events, ret, epollfd, listenfd);
	}

	close(listenfd);
	return 0;
}
