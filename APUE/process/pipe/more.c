#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/wait.h> 

#define DEF_PAGER "/bin/more"
#define LINE_LENGTH 128

int main(int argc, char *argv[])
{
	int n;
	int fd[2];
	pid_t pid;
	char line[LINE_LENGTH];
	char *pager, *argv0;
	FILE *fp;
	
	if (argc != 2)
	{
		fprintf(stderr, "pls input a file name\n");
		exit(1);
	}

	if ((fp = fopen(argv[1], "r")) == NULL)	
	{
		fprintf(stderr, "can't open %s \n", argv[1]);
		exit(1);
	}
	
	if (pipe(fd) <0)
	{
		fprintf(stderr, "pipe error\n");
		exit(1);
	}
	
	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if (pid > 0)
		{
			// parent
			close(fd[0]);

			if (fd[1] != STDOUT_FILENO)	
			{
				if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
					fprintf(stderr, "dup2 error");
			
				close(fd[1]);
			}

			while (fgets(line, LINE_LENGTH, fp) != NULL)
			{
				n = strlen(line);
				
				if (write(STDOUT_FILENO, line, n) != n)
				{
					fprintf(stderr, "write error\n");
					exit(1);
				}
			}
			
			close(fd[1]);

			if (waitpid(pid, NULL, 0) < 0)
			{
				fprintf(stderr, "waitpid error");
				exit(1);
			}
			
			exit(0);
		}
		else	
		{
			// child
			close(fd[1]);
			
			if (fd[0] != STDIN_FILENO)	
			{
				if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
					fprintf(stderr, "dup2 error");
			
				close(fd[0]);
			}

			if ((pager = getenv("PAGER")) == NULL)
				pager = DEF_PAGER;
			
			if ((argv0 = strrchr(pager, '/')) != NULL)
				argv0++;
			else
				argv0 = pager;

			if (execl(pager, argv0, (char *)0) < 0)
			{
				fprintf(stderr, "execl error");
				exit(1);
			}
		}
	return 0;
}
