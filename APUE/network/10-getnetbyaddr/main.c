/*
 * getnetbyaddr only search address in file /etc/networks ?
 * What's the use of getnetbyaddr ?
 */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct in_addr net_addr;
    struct netent *net_info;

    if (argc != 2) {
        printf("./a.out 127.0.0.1\n");
        exit(EXIT_FAILURE);
    }

    printf("argv[1]:%s\n", argv[1]);
    inet_aton(argv[1], &net_addr);
    net_info = getnetbyaddr((unsigned int)net_addr.s_addr, AF_INET);

    if(net_info == NULL) {
        perror("failed getnetbyaddr");
        exit(1);
    }
    
    printf("name: %s\n", net_info->n_name);
    printf("type: %d\n", net_info->n_addrtype);
    printf("length: %d\n", net_info->n_net);
      
    int i;
    for(i=0;;i++) {
        char *p = net_info->n_aliases[i];
        printf("addr: %s\n", p);
        if (!net_info->n_aliases[i+1]) {
            break;
        }
    } 

    return 0;
}
