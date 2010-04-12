#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>

int main(int argc, char *argv[])
{
	int fd;
	if ((fd = open("./tmp_file", O_APPEND)) < 0)
	{
		fprintf(stderr, "open file error\n");
		exit;
	}
	
	if (flock(fd, LOCK_EX) < 0)
	{
		fprintf(stderr, "lock file EX error\n");
		exit;
	}
	else	
		fprintf(stdout, "lock file EXCLUSIVE successfully\n");

	sleep(30);

//	if (flock(fd, LOCK_UN) < 0)
//	{
//		fprintf(stderr, "unlock file error\n");
//	}
//	else	
//		fprintf(stdout, "unlock file successfully\n");

	return 0;
}
