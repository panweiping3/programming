/*
 * gethostbyaddr only search address in file /etc/hosts.
 */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct in_addr host_addr;
    struct hostent *host_info;

    if (argc != 2) {
        printf("./a.out 127.0.0.1\n");
        exit(EXIT_FAILURE);
    }

    printf("argv[1]:%s\n", argv[1]);
    inet_aton(argv[1], &host_addr);
    host_info = gethostbyaddr(&host_addr, 4, AF_INET);

    if(host_info == NULL) {
        perror("failed gethostbyaddr");
        exit(1);
    }
    
    printf("name: %s\n", host_info->h_name);
    printf("type: %d\n", host_info->h_addrtype);
    printf("length: %d\n", host_info->h_length);
      
    int i;
    for(i=0;;i++) {
        char *ip;
        ip = (char *)inet_ntoa(*(struct in_addr *)host_info->h_addr_list[i]);
        printf("addr: %s\n", ip);
        if (!host_info->h_addr_list[i+1]) {
            break;
        }
    } 

    return 0;
}
