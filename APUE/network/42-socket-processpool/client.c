#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <arpa/inet.h>


#define SERVER_PORT 20000 // define the defualt connect port id
#define CLIENT_PORT ((20001+rand()) % 65536) // define the defualt client port as a random port
#define BUFFER_SIZE 256

int main(int argc, char **argv)
{    
	int client_fd;
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

	while (1)
	{
		int pipefd[2];
		pipe(pipefd);

		splice(STDIN_FILENO, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
		splice(pipefd[0], NULL, client_fd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
		char buf[BUFFER_SIZE];
		memset(buf, '\0', BUFFER_SIZE);
		int ret = recv(client_fd, buf, BUFFER_SIZE, 0);
		if (ret > 0)
			printf("%s\n", buf);
		else
			break;
	}

	close(client_fd);

	return 0;
}
