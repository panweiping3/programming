#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 

int main(int argc, char *argv[])
{
	int n;
	int fd[2];
	pid_t pid;
	char line[128];

	if (pipe(fd) < 0)
	{
		fprintf(stderr, "pipe error\n");
		exit(1);	
	}

	if ((pid = fork()) <0)
	{
		fprintf(stderr, "fork error\n");
		exit(1);	
	}
	else 
	{
		fprintf(stdout, "fd[0] is:%d\n", fd[0]);
		fprintf(stdout, "fd[1] is:%d\n", fd[1]);
		if (pid > 0)
		{
			//parent
			close(fd[0]);	
			while (1)
			{
				memset(line, '\0', 128);
				fgets(line, 128, stdin);
				write(fd[1], line, strlen(line));
                if (strcmp(line, "q\n") == 0) {
                    exit(0);
                }
			}
		}
		else
		{
			//child
			close(fd[1]);
			while (1)
			{
				memset(line, '\0', 128);
				n = read(fd[0], line, 128);
				fprintf(stdout, "line:%s\n", line);
                if (strcmp(line, "q\n") == 0) {
                    exit(0);
                }
			}
		}
	}	
	return 0;
}
