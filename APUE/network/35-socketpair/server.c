#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 255

int main(int argc, char **argv)
{
	pid_t pid;
	int fd[2];
	char buf[BUFFER_SIZE] = {'\0'};

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, fd))
		return -1;
	
	if ((pid = fork()) == 0) {
		// child process
		printf("Hi, I am children, I will send data to parent\n");
		sleep(5);
		strcpy(buf, "hello, I am in child.");
		write(fd[1], buf, strlen(buf));
	} else {
		// parent process
		memset(buf, '\0', BUFFER_SIZE);
		if (read(fd[0], buf, BUFFER_SIZE))
			printf("Hi, I am parent, I got data from child:%s\n", buf);
	}

	return 0;
}


