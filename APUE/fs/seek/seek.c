#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define 	NUM 	14
int main()
{
	int fd;

	if ((fd = open("tmpfile", O_WRONLY)) < 0) {
		perror("open error");
		exit(1);
	}

	if (lseek(fd, 1, SEEK_SET) == -1) {
		perror("lseek error");
		exit(3);
	}

	if (write(fd, "eeee", 4) != 4) {
		perror("write error");
		exit(2);
	}

	return 0;
}
