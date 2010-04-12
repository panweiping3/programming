#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t ntid;

void printids(const char *s)
{
	pid_t	pid;
	pthread_t tid;
	
	pid = getpid();
	tid = pthread_self();
	
	printf("%s pid %u tid %u (0x%x)\n", 
			s, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}

void *thr_fn(void *arg)
{
	printids("new thread: ");
	(*((int *)arg))++;
	(*((int *)arg))++;
	
	//pthread_exit(arg);	
	return arg;
}

int main(void)
{
	int err;
	int i = 9;		
	int j = 0;
	int *p = &j;
	printf("i = %d  j = %d \n", i, j);
	err = pthread_create(&ntid, NULL, thr_fn, (void *)&i);
	
	if (err != 0)
	{
		fprintf(stderr, "create new thread error");
		return -1;
	}

	printids("main thread:");
	
	sleep(1);
	printf("i = %d\n", i);
	pthread_join(ntid, (void **)&p);
	printf("*p = %d\n", *p);
	exit(0);
}

