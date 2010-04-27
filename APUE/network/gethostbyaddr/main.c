#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>

int main(void)
{
    struct in_addr host_addr;
    struct hostent *host_info;

    inet_aton("127.0.0.1", &host_addr);
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
