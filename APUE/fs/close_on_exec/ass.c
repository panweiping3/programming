#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])  
{  
    int fd;  
    printf("argc = %d\n",argc);  
    fd = *argv[1];  
    printf("fd = %d\n",fd);  
    char *s = "zzzzzzzzzzzzzzzzzzz";  
    write(fd, (void *)s, strlen(s));  
    close(fd);  
    return 0;  
}  
