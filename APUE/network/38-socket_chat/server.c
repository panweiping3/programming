#define _GNU_SOURCE 1

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define USER_LIMIT 5
#define BUFFER_SIZE 64
#define FD_LIMIT 65535

struct client_data {
	struct sockaddr_in address;
	char *write_buf;
	char buf[BUFFER_SIZE];
};

int setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

int main(int argc, char **argv)
{    
	int i, ret;
	int user_counter = 0;
	struct pollfd fds[USER_LIMIT+1];
	struct client_data *users = NULL;
	const char *ip;
	int port;

	int listenfd;
	struct sockaddr_in server_addr;

	if (argc <= 2 ) {
		printf("usage: ./server ip_address port_number\n");
		return 1;
	}

	ip = argv[1];
	port = atoi(argv[2]);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(listenfd != -1);

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &server_addr.sin_addr);
	server_addr.sin_port = htons(port);
	
	ret = bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	assert(ret != -1);

	ret = listen(listenfd, 5);
	assert(ret != -1);

	users = malloc(FD_LIMIT * sizeof(struct client_data));
	assert(users != NULL);

	fds[0].fd = listenfd;
	fds[0].events = POLLIN | POLLERR;
	fds[0].revents = 0;
	for (i=1; i<=USER_LIMIT; ++i) {
		fds[i].fd = -1;
		fds[i].events = 0;
	}

	while (1) {
		ret = poll(fds, user_counter + 1, -1);
		if (ret < 0) {
			printf("poll failure\n");
			break;
		}

		for (i=0; i < user_counter + 1; ++i) {
			if ((fds[i].fd == listenfd) && (fds[i].revents & POLLIN)) {
				struct sockaddr_in client_address;
				socklen_t client_addrlen = sizeof(client_address);
				int connfd = accept(listenfd,
						(struct sockaddr *)&client_address,
						&client_addrlen);
				if (connfd < 0) {
					printf("errno is:%d\n", errno);
					continue;
				}

				if (user_counter >= USER_LIMIT) {
					const char *info = "two many users\n";
					printf("%s", info);
					send(connfd, info, strlen(info), 0);
					close(connfd);
					continue;
				}

				user_counter++;
				users[connfd].address = client_address;
				setnonblocking(connfd);
				fds[user_counter].fd = connfd;
				fds[user_counter].events = POLLIN | POLLRDHUP | POLLERR;
				fds[user_counter].revents = 0;
				printf("comes a new user %d, now have %d users\n",
					connfd, user_counter);
			} else if (fds[i].revents & POLLERR) {
				char errors[100];
				printf("get an error from %d\n", fds[i].fd);
				memset(errors, '\0', 100);
				socklen_t length = sizeof(errors);
				if (getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR,
					&errors, &length) < 0) {
					printf("get socket option failed\n");
				}
				continue;
			} else if (fds[i].revents & POLLRDHUP) {
				users[fds[i].fd] = users[fds[user_counter].fd];
				close(fds[i].fd);
				fds[i] = fds[user_counter];
				i--;
				user_counter--;
				printf("a client left\n");
			} else if (fds[i].revents & POLLIN) {
				int connfd = fds[i].fd;
				memset(users[connfd].buf, '\0', BUFFER_SIZE);
				ret = recv(connfd, users[connfd].buf, BUFFER_SIZE-1, 0);
				users[connfd].buf[ret-1] = '\0';
				if (ret < 0) {
					if (errno != EAGAIN) {
						close(connfd);
						users[fds[i].fd] = users[fds[user_counter].fd];
						fds[i] = fds[user_counter];
						i--;
						user_counter--;
					}
				} else if (ret == 0) {
					printf("why we get here ?\n"); 
				} else {
					int j;
					printf("get %d bytes of client data %s from %d\n",
						ret, users[connfd].buf, connfd);
					for (j=1; j<=user_counter; ++j) {
						if (fds[j].fd == connfd)
							continue;
						fds[j].events |= ~POLLIN;
						fds[j].events |= POLLOUT;
						users[fds[j].fd].write_buf = users[connfd].buf;
					}
				}
			} else if (fds[i].revents & POLLOUT) {
				int connfd = fds[i].fd;
				if (!users[connfd].write_buf)
					continue;
				ret = send(connfd, users[connfd].write_buf,
					strlen(users[connfd].write_buf), 0);
				users[connfd].write_buf = NULL;
				fds[i].events |= ~POLLOUT;
				fds[i].events |= POLLIN;
			}
		}
	}

	free(users);
	close(listenfd);

	return 0;
}

