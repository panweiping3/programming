#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>

int main(int argc, char *argv[])
{
	int fd;
	if ((fd = open("./tmp_file", O_RDWR)) < 0)
	{
		fprintf(stderr, "open file error\n");
		exit;
	}
	else
		fprintf(stdout, "open file successfully\n");
	
	if (flock(fd, LOCK_EX | LOCK_NB) < 0)
		fprintf(stderr, "lock file EXCLUSIVE error\n");
	else
		fprintf(stdout, "lock file EXCLUSIVE successfully\n");
	

	if (flock(fd, LOCK_SH | LOCK_NB) < 0)
	{
		fprintf(stderr, "lock file SHARED error\n");
	}
	else
		fprintf(stdout, "lock file SHARED successfully\n");

	if (write(fd, "pwp", 3) < 3)
	{
		perror("error pwp:");	
	}

	close(fd);
	return 0;
}
