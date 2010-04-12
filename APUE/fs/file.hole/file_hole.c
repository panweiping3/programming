#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define 	NUM 	14
int main()
{
	char buf1[NUM] = "abcd";
	char buf2[NUM] = "ABCDEFGHIJKLMN";
	
	int fd;

	if ((fd = creat("file.hole", O_RDWR)) < 0)
	{
		perror("create file.hole error");
	
		exit(1);
	}

	if (write(fd, buf1, NUM) != NUM)
	{
		perror("write buf1 error");
		
		exit(2);
	}

	if (lseek(fd, 16348, SEEK_SET) == -1)
	{
		perror("lseek error");

		exit(3);
	}

	if (write(fd, buf2, NUM-2) != NUM-2)
	{
		perror("write buf2 error");

		exit(4);
	}

	return 0;
}
