/* Tcp client program, It is a simple example only.

 * zhengsh 200520602061 2

 * connect to server, and echo a message from server.

 */

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT 20000 // define the defualt connect port id
#define CLIENT_PORT ((20001+rand()) % 65536) // define the defualt client port as a random port
#define BUFFER_SIZE 255
#define REUQEST_MESSAGE "welcome to connect the server.\n"

void usage(char *name)
{
	printf("usage: %s Ip Addr\n", name);
}

int main(int argc, char **argv)
{    
	pthread_t thread_id;
	int client_fd, length = 0;
	struct sockaddr_in server_addr,client_addr;

	socklen_t socklen = sizeof(server_addr);
	char buf[BUFFER_SIZE];

	if (argc < 2)
	{
		usage(argv[0]);
		exit(1);
	}

	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("create socket error!\n");
		exit(1);
	}

	srand(time(NULL));//initialize random generator
	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(CLIENT_PORT);
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_aton(argv[1], &server_addr.sin_addr);
	server_addr.sin_port = htons(SERVER_PORT);

	if (connect(client_fd, (struct sockaddr*)&server_addr, socklen) < 0)
	{
		printf("can't connect to %s!\n",argv[1]);
		exit(1);
	}

	while (1)
	{
		int size = 0;
		sleep(1);
		memset(buf, 'a', BUFFER_SIZE);
		size = recv(client_fd, buf, BUFFER_SIZE, 0);

		if (size <= 0){
			close (client_fd);
			break;
		} else {
			printf("size=%d\n", size);
		}
	}

	return 0;

}
