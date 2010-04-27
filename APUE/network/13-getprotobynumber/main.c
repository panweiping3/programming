/*
 * getprotobynumber only search name in file /etc/protocols.
 */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct protoent *proto_info;

    if (argc != 2) {
        printf("./a.out number\n");
        exit(EXIT_FAILURE);
    }

    printf("argv[1]:%s\n", argv[1]);
    proto_info = getprotobynumber(atoi(argv[1]));

    if(proto_info == NULL) {
        perror("failed getprotobyaddr");
        exit(1);
    }
    
    printf("name: %s\n", proto_info->p_name);
    printf("proto: %d\n", proto_info->p_proto);
      
    int i;
    for(i=0;;i++) {
        char *p = proto_info->p_aliases[i];
        printf("aliases: %s\n", p);
        if (!proto_info->p_aliases[i+1]) {
            break;
        }
    } 

    return 0;
}
