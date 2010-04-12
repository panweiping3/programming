#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 80
void sigint_handler(int sig);

int main()
{
	char buf[MAXLINE] = {'\0'};

	pid_t pid;

	int status = 0;

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("set sigint_handler error");
		return 1;
	}

	printf("%% ");
	
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (buf[strlen(buf)-1] == '\n')
			buf[strlen(buf)-1] = '\0';

		if ((pid = fork()) < 0)
		{
			fprintf(stderr, "fork error\n");
			exit(1);
		}
		else if (pid == 0)
			 {
				execlp(buf, buf, (char *)0);
				perror("error");
				fprintf(stderr, "execlp error\n");
				exit(127);
			 }

		if ((pid = waitpid(pid, &status, 0)) < 0)
		{
			fprintf(stderr, "waitpid error\n");
			exit(2);
		}
		
		printf("%% ");
	}

	return 0;
}

void sigint_handler(int sig)
{
	printf("SIGINT occur\n");	
}
