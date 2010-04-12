#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#define SERVER_PORT  10000 

int main(int argc, char *argv)
{
	int sk;
	char cmd[32];
	char buf[4096];

 	struct sockaddr_in servaddr;
 	int servaddr_length;
	
	sk = socket(PF_INET, SOCK_STREAM, 0);
	
	if (sk == -1)
	{
		fprintf(stderr, "Can't create socket\n");
		
		return -1;
	}
	
	servaddr_length = sizeof(struct sockaddr_in);
	bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_aton("127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(SERVER_PORT);
       
	if (connect(sk, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
     	fprintf(stderr, "connect server failure!\n");
        return -3;
	}

    fprintf(stdout, "connect server successfully!\n");

	memset(cmd, '\0', 32);
	gets(cmd);

    while (strcmp(cmd, "q") != 0)
	{
		send(sk, cmd, 32, 0);
		
		if (recv(sk, buf, 4096, 0) >0)
			fprintf(stdout, buf, 4096);

		memset(cmd, '\0', 32);
		memset(buf, '\0', 4096);
		gets(cmd);
	}

	return 0;
}

