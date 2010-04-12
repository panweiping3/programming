#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>

int main(int argc, char *argv[])
{
	int fd;
	struct stat stat_buf;
	struct utimbuf utime_buf;

	if (stat(argv[1], &stat_buf) != 0)
	{
		perror("stat error");
		exit(1);
	}

	if ((fd = open(argv[1], O_RDWR | O_TRUNC)) < 0)
	{
		perror("stat error");
		exit(1);
	}

	close(fd);

	utime_buf.actime = stat_buf.st_atime;	
	utime_buf.modtime = stat_buf.st_mtime;	

	if (utime(argv[1], &utime_buf) < 0)
	{
		perror("utime error");
		exit(1);
	}

	return 0;
}


