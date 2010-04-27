/*
 * getservbyname only search name in file /etc/services.
 * NOTE:
 * serv_info->s_port is network byte order.
 */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct servent *serv_info;

    if (argc != 3) {
        printf("./a.out name protocol\n");
        exit(EXIT_FAILURE);
    }

    printf("argv[1]:%s\n", argv[1]);
    serv_info = getservbyname(argv[1], argv[2]);

    if(serv_info == NULL) {
        perror("failed getservbyaddr");
        exit(1);
    }
    
    printf("name: %s\n", serv_info->s_name);
    printf("port: %d\n", ntohs(serv_info->s_port));
    printf("proto: %s\n", serv_info->s_proto);
      
    int i;
    for(i=0;;i++) {
        char *p = serv_info->s_aliases[i];
        if (!p) {
            printf("aliases: %s\n", p);
        } else {
            break;
        }
        if (!serv_info->s_aliases[i+1]) {
            break;
        }
    } 

    return 0;
}
