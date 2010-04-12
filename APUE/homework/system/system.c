#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int mysystem(const char *cmd);
int check_shell_available(void);

int main(int argc, char *argv[])
{
	int status;
	int i;
	char args[1024];

	if (argc <= 1 )
	{
		fprintf(stderr, "please input commands\n");
		return 1;
	}
	
	for (i=1; i<argc; i++)
	{
		strcat(args, argv[i]);
		strcat(args, " ");
	}

	status = mysystem(args);		
	
	return status;
}

int mysystem(const char *cmd)
{
	int status;
	pid_t pid;

	if (cmd == NULL)
	{
		if (check_shell_available() == 0)
			return 1;
		else
			return 0;
	}

	if ((pid = fork()) < 0)
	{
		status = -1;
	}
	else if (pid == 0)
	{
		execl("/bin/sh", "sh", "-c", cmd, NULL);
		_exit(127);
	}
	else
	{
		if(waitpid(pid, &status, 0) < 0)
		{
				status = -1;
		}
	}	
	
	return status;
}

int check_shell_available(void)
{
	struct stat stat_buf;
	
	return lstat("/bin/sh", &stat_buf);
}
