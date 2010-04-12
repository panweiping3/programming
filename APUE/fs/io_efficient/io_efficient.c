#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZ 4096

void set_fl(int fd, int flags);
int main()
{
	int n;
	char buf[BUFSIZ] = {'\0'};

	printf("BUFSIZ is %d\n", BUFSIZ);

	set_fl(STDOUT_FILENO, O_SYNC);

	while ((n = read(STDIN_FILENO, buf, BUFSIZ)) > 0)
	{
		if (write(STDOUT_FILENO, buf, n) != n)
		{
			perror("write to STDOUT_FILENO error");
			
			exit(1);
		}
	}

	if (n < 0)
	{
		perror("read error");
		
		exit(2);
	}

	fsync(STDOUT_FILENO);	
	return 0;
}

void set_fl(int fd, int flags)
{
	int val;
	
	if ((val = fcntl(fd, F_GETFL)) < 0)
	{
		perror("get fcntl error");
		
		exit(1);
	}

	val |= flags;

	if (fcntl(fd, F_SETFL, val) < 0)
	{
		perror("set fcntl error");
		
		exit(1);
	}

	return;
}
