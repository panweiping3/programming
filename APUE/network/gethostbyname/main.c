/* 
 * Maybe it can lookup ip address of sina ?
 *
 */

#include   <stdio.h>  
#include   <stdlib.h>  
#include   <sys/types.h>  
#include   <sys/socket.h>  
#include   <netinet/in.h>  
#include   <arpa/inet.h>  
#include   <netdb.h>  

int main(int argc, char *argv[])  
{  
    int i;
    struct   hostent *hp;  
    char *p;  
    const char *hostname = argv[1];  
    char addr_str[INET_ADDRSTRLEN];
    if (argc != 2) {
        fprintf(stderr, "./a.out name\n");
        return 2;
    }

    printf("%s\t", hostname);
    hp = gethostbyname(hostname);  
    if (!hp) {  
        printf("host information not found !\n");  
        return;  
    }  

    printf("%s\t", hp->h_name);
    for (i=0; ; i++) {
        p = hp->h_addr_list[i];
        if (p) {
            if (!inet_ntop( AF_INET, 
                            (void *)p, 
                            addr_str, 
                            INET_ADDRSTRLEN)) {
                fprintf(stderr, "inet_ntop error\n");
                exit (2);
            }
            printf("%s\t", addr_str);
        } else {
            printf("\n");
            break;
        }
    }

    return 0;    
}   

