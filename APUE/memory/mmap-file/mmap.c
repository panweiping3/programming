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
	void *src, *src_old;
	int i;

	struct stat statbuf;

fprintf(stderr, "%d\n", __LINE__);	
	if ((fd_in = open(argv[1], O_RDWR)) < 0)
	{
		fprintf(stderr, "open %s error \n", argv[1]);
		exit(1);
	}

fprintf(stderr, "%d\n", __LINE__);	
	if (fstat(fd_in, &statbuf) < 0)
	{
		fprintf(stderr, "stat %s error \n", argv[1]);
		exit(1);
	}
	
//	if (lseek(fd_out, statbuf.st_size-1, SEEK_SET) == -1)

fprintf(stderr, "%d\n", __LINE__);	
	if ((src = mmap(0, statbuf.st_size + 1024*1024, PROT_READ, MAP_SHARED, fd_in, 0)) == MAP_FAILED)
	{
		fprintf(stderr, "mmap %s error \n", argv[1]);
		exit(1);
	}
fprintf(stderr, "%d\n", __LINE__);	
	src_old = src;
	src += statbuf.st_size;
	
	for (i = 0; i < 1024 * 1024; ++i) {
fprintf(stderr, "%d\n", __LINE__);	
		*((char *)src) = 'a';	
	}

fprintf(stderr, "%d\n", __LINE__);	
	msync(src_old, statbuf.st_size + 1024*1024, 0);	
	
fprintf(stderr, "%d\n", __LINE__);	
	munmap(src_old, statbuf.st_size + 1024*1024);
fprintf(stderr, "%d\n", __LINE__);	
		
	return 0;
}



















