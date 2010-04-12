#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	struct stat stat_buf;

	if (stat("foo", &stat_buf) < 0)
	{
		perror("stat foo error");
		
		exit(1);
	}

	if (chmod("foo", (stat_buf.st_mode | S_ISGID)) < 0)
	{
		perror("chmod foo error");
		
		exit(2);
	}

#if 0
	if (chmod("foo", S_IRUSR | S_IWUSR | S_IRGRP |S_IROTH) < 0)
	{
		perror("chmod foo error");
		
		exit(2);
	}
#endif
	return 0;	
}

