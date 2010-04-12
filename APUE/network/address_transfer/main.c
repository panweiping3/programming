#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    char addr_str[INET_ADDRSTRLEN] = "172.16.82.38";
    char addr_str2[INET_ADDRSTRLEN] = "172.16.82.38";

    struct sockaddr_in addr;

    if (inet_pton(AF_INET, addr_str, (void *)&addr) <=0 ) {
        fprintf(stderr, "inet_pton error\n");
        exit (1);
    }

    if (!inet_ntop(AF_INET, (void *)&addr, addr_str2, INET_ADDRSTRLEN)) {
        fprintf(stderr, "inet_ntop error\n");
        exit (2);
    }

    fprintf(stderr, "address1 %s\n", addr_str);
    fprintf(stderr, "address2 %s\n", addr_str2);
    exit (0);
}
