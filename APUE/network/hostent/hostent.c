#include <stdio.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int i;
    struct hostent *hostent_p = NULL;
    char addr_str[INET_ADDRSTRLEN];
    
    sethostent(0);
    while ((hostent_p = gethostent()) != NULL) {
        printf("hostent_p->h_name: %s\n", hostent_p->h_name);
        printf("hostent_p->h_addrtype: %d\n", hostent_p->h_addrtype);
        printf("hostent_p->h_length: %d\n", hostent_p->h_length);

        for(i=0; ; i++) {
            if (!inet_ntop(AF_INET, (void *)&hostent_p->h_addr_list[i], 
                            addr_str, INET_ADDRSTRLEN)) {
                fprintf(stderr, "inet_ntop error\n");
                exit (2);
            }
            printf("\naddr: %s\n", addr_str);
            if(hostent_p->h_addr_list[i] + hostent_p->h_length >= hostent_p->h_name) {
                break;
            }
        } 

        hostent_p = NULL;
        printf("\n\n");
    }

    endhostent();
}
