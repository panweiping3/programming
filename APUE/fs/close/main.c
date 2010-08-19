#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <linux/unistd.h>
#include <sys/syscall.h>

int main(int argc, char *argv[])
{
    int fd,size,len;
	int i;
    char *buf="Hello!I'm writing to this file!\n";
    len=strlen(buf);

    if((fd = open("/tmp/hello.c", O_CREAT|O_TRUNC|O_RDWR, 0666)) < 0) {
        perror("open:");
        exit(1);
    } else {
        printf("open file:hello.c %d\n", fd);
    }

	for (i=0;i<1048;++i) {
   	 	if((size = write(fd, buf, len)) < 0) {
        	perror("write:");
        	exit(1);
    	} else {
        	printf("Write:%s\n", buf);
    	}
	}
/*	
    if(close(fd)<0) {
        perror("close:");
        exit(1);
    } else {
        printf("Close hello.c\n");
    }
*/
	syscall(SYS_close, fd);
	pause();
    exit(0);
}
