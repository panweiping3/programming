#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define OPTSTR "i:p:h"
#define DATA 'a'

void help()
{
    printf("i: server ip address\n");
    printf("p: server port number\n");
    printf("h: this help\n");
    exit(1);
}

int main(int argc, char *argv[])
{
    int client_fd;
    int server_len,client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    struct in_addr server_ip;
    server_ip.s_addr = 0;
    int server_port = 0;

	if (argc == 1)
	{
		fprintf(stderr, "argc error\n");
        help();
	}	

    char c;
	while ((c = getopt(argc, argv, OPTSTR)) != EOF)
	{
		switch (c)
		{
			case 'i':
                server_ip.s_addr = inet_addr(optarg);
				break;
			case 'p':
                server_port = atoi(optarg);
				break;
			case 'h':
                help();
                break;
            default:
                help();
		}
	}
    
    if (server_ip.s_addr == 0 || server_port == 0) {
        help();
    }

    fprintf(stderr, "%s %d %s server ip=%s\n", __FILE__, __LINE__, __func__, inet_ntoa(server_ip));   
    fprintf(stderr, "%s %d %s server ip=%u\n", __FILE__, __LINE__, __func__, server_ip.s_addr);   
    fprintf(stderr, "%s %d %s server ip=%x\n", __FILE__, __LINE__, __func__, server_ip.s_addr);   
    fprintf(stderr, "%s %d %s server port=%d\n", __FILE__, __LINE__, __func__, server_port);   
    close(client_fd);
    exit(0);
}
