#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void set_fl(int fd, int flags);

int main(int argc, char *argv[])
{
	int val;
	
	if (argc != 2)
	{
		fprintf(stderr, "command line arguments is erong\n");
	
		exit(1);
	}

	if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
	{
		perror("fcntl error");
		
		exit(2);
	}

	switch (val & O_ACCMODE)
	{
		case O_RDONLY:
				fprintf(stdout, "read only\n");
				break;
		case O_WRONLY:
				fprintf(stdout, "write only\n");
				break;
		case O_RDWR:
				fprintf(stdout, "read and write\n");
				break;
		default:
				fprintf(stdout, "unknown access mode\n");
				break;
	}

	if (val & O_APPEND)
		fprintf(stdout, "append mode\n");

	if (val & O_NONBLOCK)
		fprintf(stdout, "nonblocking\n");

		if (val & O_SYNC)
			fprintf(stdout, "synchronous mode\n");

	putchar('\n');

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

