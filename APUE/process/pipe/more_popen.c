#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <errno.h> 

#define PAGER "${PAGER:-more}"
#define LINE_LENGTH 128

FILE *ppopen(const char *cmdstring, const char *type);
int ppclose(FILE *fp);

int main(int argc, char *argv[])
{
	char line[LINE_LENGTH];
	FILE *fpin, *fpout;
	
	if (argc != 2)
	{
		fprintf(stderr, "pls input a file name\n");
		exit(1);
	}

	if ((fpin = fopen(argv[1], "r")) == NULL)	
	{
		fprintf(stderr, "can't open %s \n", argv[1]);
		exit(1);
	}
	
	if ((fpout = ppopen(PAGER, "w")) == NULL)
	{
		fprintf(stderr, "popen error\n");
		exit(1);
	}

	while (fgets(line, LINE_LENGTH, fpin) != NULL)
	{
		if (fputs(line, fpout) == EOF)
		{
			fprintf(stderr, "fputs error\n");
			exit(1);
		}
	}
	
	if (ferror(fpin))
	{
		fprintf(stderr, "fpin error");
		exit(1);
	}
	
	if (ppclose(fpout) < 0)
	{
		fprintf(stderr, "pclose error");
		exit(1);
	}

	return 0;
}


static pid_t *childpid = NULL;
static int maxfd = 256;

FILE *ppopen(const char *cmdstring, const char *type)
{
	int i;
	int pfd[2];
	pid_t pid;
	FILE *fp = NULL;

	if ((type[0] != 'r' && type[0] != 'w') || type[1] != '\0')
	{
		fprintf(stderr, "only support read and write\n");
		errno = EINVAL;
		return NULL;
	}

	if (childpid == NULL)
	{
		if ((childpid = calloc(maxfd, sizeof(pid_t))) == NULL)
		{
			fprintf(stderr, "calloc error\n");
			return NULL;	
		}
	}
	
	if (pipe(pfd) < 0)
	{
		fprintf(stderr, "pipe error\n");	
		return NULL;
	}

	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "fork error\n");
		return NULL;
	}
	else if (pid == 0)	
		{
			// child
			if (*type == 'r')
			{
				close(pfd[0]);
				
				if (pfd[1] != STDOUT_FILENO)
				{
					dup2(pfd[1], STDOUT_FILENO);
					close(pfd[1]);
				}
			}
			else
			{
				close(pfd[1]);
				
				if (pfd[0] != STDIN_FILENO)
				{
					dup2(pfd[0], STDIN_FILENO);
					close(pfd[0]);
				}
			}
			
			for (i=0; i< maxfd; i++)
				if (childpid[i] > 0)
					close(i);

			execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		
			_exit(127);	
		}
	
	// parent continues;
	if (*type == 'r')
	{
		close(pfd[1]);
		if ((fp = fdopen(pfd[0], type)) == NULL)
		{
			fprintf(stderr, "fdopen error\n");
			return NULL;
		}
	}
	else
	{
		close(pfd[0]);
		if ((fp = fdopen(pfd[1], type)) == NULL)
		{
			fprintf(stderr, "fdopen error\n");
			return NULL;
		}
	}

	childpid[fileno(fp)] = pid;

	return fp;
}

int ppclose(FILE *fp)
{
	int fd, stat;
	pid_t pid;

	if (childpid == NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	fd = fileno(fp);
	if ((pid = childpid[fd]) == 0)
	{
		errno = EINVAL;
		return (-1);
	}

	childpid[fd] = 0;
	
	if (fclose(fp) == EOF)
		return -1;

	while (waitpid(pid, &stat, 0) < 0)
	{
		if (errno != EINTR)
			return (-1);
	}

	return (stat);
}













