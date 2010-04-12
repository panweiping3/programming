#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	int n;
	int fd[2];
	pid_t pid;
	char line[128];

	if ((pid = fork()) <0)
	{
		fprintf(stderr, "fork error\n");
		exit(1);	
	}
	else if (pid > 0)
		{
			//parent
			fd[0] = open("./fifo1", O_WRONLY);

			while (1)
			{
				memset(line, '\0', 128);
				gets(line);
				write(fd[0], line, strlen(line));
			}
		}
		else
		{
			//child
			fd[1] = open("./fifo1", O_RDONLY);
			while (1)
			{
				memset(line, '\0', 128);
				n = read(fd[1], line, 128);
				fprintf(stdout, "line:%s\n", line);
			}
		}

	return 0;
}
