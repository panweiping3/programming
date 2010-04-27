/*
 * this program is to read file /etc/hosts,
 * TODO:
 * What's the use of /etc/hosts ?
 */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int i;
    char *p;
    struct hostent *hostent_p = NULL;
    char addr_str[INET_ADDRSTRLEN];
    
    sethostent(0);
    while ((hostent_p = gethostent()) != NULL) {
        printf("hostent_p->h_name: %s\n", hostent_p->h_name);
        printf("hostent_p->h_addrtype: %d\n", hostent_p->h_addrtype);
        printf("hostent_p->h_length: %d\n", hostent_p->h_length);

        for (i=0; ; i++) {
            p = hostent_p->h_aliases[i];
            if (p) {
                fprintf(stdout, "hostent_p->h_aliases[%d]=%s\n", i, p);
            } else {
                break;
            }
        }
        for (i=0; ; i++) {
            p = hostent_p->h_addr_list[i];
            if (p) {
                if (!inet_ntop( AF_INET, 
                                (void *)p, 
                                addr_str, 
                                INET_ADDRSTRLEN)) {
                    fprintf(stderr, "inet_ntop error\n");
                    exit (2);
                }
                printf("addr[%d]: %s\n", i, addr_str);
            } else {
                break;
            }
        }
        hostent_p = NULL;
        printf("\n\n");
    }

    endhostent();
}
