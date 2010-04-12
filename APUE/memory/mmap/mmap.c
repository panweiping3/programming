#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
	int fd_in, fd_out;
	void *src, *dest;

	struct stat statbuf;

	if (argc != 3)
	{
		fprintf(stderr, "incorrect args! \n");
		exit(1);
	}

	if ((fd_in = open(argv[1], O_RDONLY)) < 0)
	{
		fprintf(stderr, "open %s error \n", argv[1]);
		exit(1);
	}

	if ((fd_out = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0)
	{
		fprintf(stderr, "open %s error \n", argv[2]);
		exit(1);
	}
	
	if (fstat(fd_in, &statbuf) < 0)
	{
		fprintf(stderr, "stat %s error \n", argv[1]);
		exit(1);
	}
	
	if (lseek(fd_out, statbuf.st_size, SEEK_SET) == -1)
	{
		fprintf(stderr, "lseek %s error \n", argv[2]);
		exit(1);
	}	

	if (write(fd_out, "pwp\n", 4) < 3)
	{
		fprintf(stderr, "write %s error \n", argv[2]);
		exit(1);
	}	
	
	if ((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fd_in, 0)) == MAP_FAILED)
	{
		fprintf(stderr, "mmap %s error \n", argv[1]);
		exit(1);
	}
	
	if ((dest = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_out, 0)) == MAP_FAILED)
	{
		fprintf(stderr, "mmap %s error \n", argv[2]);
		exit(1);
	}

	memcpy(dest, src, statbuf.st_size);
	
	return 0;
}



















