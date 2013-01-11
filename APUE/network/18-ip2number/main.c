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
    int server_fd,client_fd;
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
    fprintf(stderr, "%s %d %s server ip=%ld\n", __FILE__, __LINE__, __func__, server_ip.s_addr);   
    fprintf(stderr, "%s %d %s server ip=0X%08x\n", __FILE__, __LINE__, __func__, server_ip.s_addr);   
    fprintf(stderr, "%s %d %s server port=%d\n", __FILE__, __LINE__, __func__, server_port);   
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = server_ip.s_addr;
    server_address.sin_port = htons(server_port);
    server_len = sizeof(server_address);
    bind(server_fd, (struct sockaddr*)&server_address, sizeof(server_address));
    listen(server_fd, 1);
    printf("server is waiting\n");
    exit(0);
    client_len = sizeof(client_address);
    client_fd = accept(server_fd, (struct sockaddr*)&client_address, &client_len);
    int i = 0;
    char recv_data[1];
    while (read(client_fd, recv_data, 1) > 0){
        if (recv_data[0] != DATA) {
            exit(1);
        }
        write(client_fd, recv_data, 1);
    }
    close(client_fd);
    close(server_fd);
    exit(0);
}
