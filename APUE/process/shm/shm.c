#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>

#define ARRAY_SIZE 	40000
#define MALLOC_SIZE 10000
#define SHM_SIZE 	10000
#define SHM_MODE 	0600

char array[ARRAY_SIZE];

int main()
{
	int shmid;
	char *ptr, *shmptr;

	printf("array[] from %lx to %lx\n", (unsigned long)&array[0], (unsigned long)&array[ARRAY_SIZE]);
	printf("stack around %lx\n", (unsigned long)&shmid);
	
	if ((ptr = malloc(MALLOC_SIZE)) == NULL)
	{
		fprintf(stderr, "malloc error");
		exit(1);
	}

	printf("malloc from %lx to %lx\n", (unsigned long)ptr, (unsigned long)ptr+MALLOC_SIZE);
	
	if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)
	{
		fprintf(stderr, "shmget error");
		exit(1);
	}
	
	if ((shmptr = shmat(shmid, 0, 0)) == (void *)-1)
	{
		fprintf(stderr, "shmat error");
		exit(1);
	}

	printf("shared memory attached from %lx to %lx\n", (unsigned long)shmptr, (unsigned long)shmptr + SHM_SIZE);

	if (shmctl(shmid, IPC_RMID, 0) < 0)
	{
		fprintf(stderr, "shmctl error");
		exit(1);
	}

	exit(0);
}
