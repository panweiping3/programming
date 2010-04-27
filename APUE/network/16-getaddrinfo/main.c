#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    struct addrinfo *addr_info_p, *aip;
    struct addrinfo hint;
    const char *addr;
    char buf[INET_ADDRSTRLEN];
    struct sockaddr_in *sockaddr_in_p;

    if (argc != 3) {
        printf("./a.out host service\n");
        exit(EXIT_FAILURE);
    }

    hint.ai_flags = AI_CANONNAME;
    hint.ai_family = 6;
    hint.ai_socktype = 0;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    if (!getaddrinfo(argv[1], argv[2], &hint, &addr_info_p)) {
        perror("failed getaddrinfo");
        exit(EXIT_FAILURE);
    }
  
    for (aip = addr_info_p; aip != NULL; aip = aip->ai_next) {
        printf("flags : %d\n", aip->ai_flags);
        printf("family: %d\n", aip->ai_family);
        printf("socktype: %d\n", aip->ai_socktype);
        printf("protocol: %d\n", aip->ai_protocol);
        printf("addrlen: %d\n", aip->ai_addrlen);
        sockaddr_in_p = (struct sockaddr_in *)aip->ai_addr;
        addr = inet_ntop(AF_INET, &sockaddr_in_p->sin_addr, buf, INET_ADDRSTRLEN);
        printf("addr: %s\n", addr ? addr : "unknown");
        printf("canonname: %s\n", aip->ai_canonname);
    }

    return 0;
}
