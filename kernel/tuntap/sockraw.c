#include <stdio.h>   
#include <fcntl.h>   
#include <errno.h>   
#include <signal.h>
#include <string.h>   
#include <sys/types.h>   
#include <sys/socket.h>   
#include <sys/time.h>   
#include <netinet/in.h>   
#include <arpa/inet.h>   
#include <netdb.h>

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in source_addr;
	char * strprotocol;int protocol;
	char buf[2048];
	int addr_size;
	
	if (argc != 2) {
		fprintf(stderr, "usage:%s protocl\n", argv[0]);
		return 0;
	}
	
	strprotocol = argv[1];
	if (strstr(strprotocol,"udp")) {
		protocol = IPPROTO_UDP;
	}
	else if (strstr(strprotocol,"icmp")) {
		protocol = IPPROTO_ICMP;
	} else {
		fprintf(stderr, "invalid protocol, try 'upd' or 'icmp'");
	}	
  	
	if((sockfd = socket(AF_INET, SOCK_RAW, protocol)) < 0) {
	         perror("socket()");
	         return(-1);
	}
	
	addr_size = sizeof(source_addr);
	for(;;) {
	        int n = recvfrom(sockfd, buf, sizeof(buf), 0,(struct sockaddr*)&source_addr, &addr_size);
	        if(n == -1)
	        	perror("recvfrom()");
	        else {
	        	fprintf(stderr, "recv %d bytes\n", n);
	        	fwrite(buf, n, 1, stdout);
	        	fprintf(stderr, "\n");
	        	fflush(stdout);
	        }
	}
	return 0;
}
