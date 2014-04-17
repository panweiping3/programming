#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main()  
{  
	int fd;
	pid_t pid;  
	fd = open("test.txt",O_RDWR|O_APPEND);  
	if (fd == -1) {
		printf("fd = %d",fd); 
		exit(1);
	}
	printf("fork!\nn");  
	//fcntl(fd, F_SETFD, 1);                      
	char *s="ooooooooooooooooooo\n";  
	pid = fork();  
	if(pid == 0)  
		execl("ass", "./ass", &fd, NULL);  
	wait(NULL);  
	write(fd,s,strlen(s));  
	close(fd);  
	return 0;  
}  
