#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_fn1(void *arg)
{
	printf("thread 1 is running\n");

	return (void *)1;
}

void *thr_fn2(void *arg)
{
	printf("thread 2 is running\n");

	return (void *)2;
}

int main(void)
{
	int err;
	pthread_t tid1, tid2;
    void *tret;
  
	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
	{
		fprintf(stderr, "create new thread 1 error");
		return -1;
	}

	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
	{
		fprintf(stderr, "create new thread 1 error");
		return -2;
	}

	err = pthread_join(tid1, &tret);	
	printf("thread 1 exit code %d\n", (int)tret);
	err = pthread_join(tid2, &tret);	
	printf("thread 1 exit code %d\n", (int)tret);
	exit(0);
}

