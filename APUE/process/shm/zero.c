#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>

#define NLOOPS 		10000
#define SIZE 		sizeof(long)

static int update(long *ptr)
{
	return ((*ptr)++);
}

int main(void)
{
	int fd, i, counter;
	pid_t pid;
	void *area;

	if ((fd = open("/dev/zero", O_RDWR)) < 0)
	{
		fprintf(stderr, "open zero error\n");
		exit(1);
	}

	if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
	{
		fprintf(stderr, "mmap error\n");
		exit(1);
	}
	
	close(fd);
	
	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "fork error\n");
		exit(1);
	}else if (pid > 0)
		{
			// parent
			while (1)
			{
				counter = update((long *)area);
				fprintf(stderr, "parent: got %d\n", counter);
			}
		}else{
				while (1)
				{
					counter = update((long *)area);
					fprintf(stderr, "child: got %d\n", counter);
				}
			}

	exit(0);
}
