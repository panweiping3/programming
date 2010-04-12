#include   <stdio.h>  
#include   <string.h>  
#include   <sys/types.h>  
#include   <sys/socket.h>  
#include   <netinet/in.h>  
#include   <arpa/inet.h>  
#include   <netdb.h>  

int main(int argc, char *argv[])  
{  
    unsigned long addr;  
    struct   hostent *hp;  
    char **p;  
    const char *hostname = argv[1];  
    if (argc != 2) {
        fprintf(stderr, "./a.out name\n");
        return 2;
    }

    hp = gethostbyname(hostname);  
    if (hp == NULL) {  
        printf("host information not found !\n");  
        return;  
    }  

    for (p = hp->h_addr_list; *p != 0; p++) {  
        struct in_addr in;  
        char **q;  
        memcpy(&in.s_addr, *p, sizeof(in.s_addr));  
        printf("%s\t%s", inet_ntoa(in), hp->h_name);  
        for (q = hp->h_aliases; *q != 0; q++) {
            printf("   %s",   *q);  
        }

        putchar('\n');  
    }  

    return;    
}   

