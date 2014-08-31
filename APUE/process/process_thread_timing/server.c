#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>

void *thread_sync(void *client_fd)
{
	pthread_detach (pthread_self());
	pause();
	return NULL;
}

int main(int argc, char **argv)
{
	int i;
	pthread_t thread_id0;

	struct timeval tv;
	int T1, T2;

	gettimeofday(&tv,NULL);
	T1 = tv.tv_sec*1000*1000 + tv.tv_usec;
	
	errno = 0;
	for (i=0; i<NUM; ++i) {
		int ret = pthread_create(&thread_id0, NULL, thread_sync, NULL);
		if (ret) {
			perror("pthread_create error:");
			break;
		}
	}

	gettimeofday(&tv,NULL);

	T2 = tv.tv_sec*1000*1000+tv.tv_usec;

	printf("i=%d T2-T2=%d, (T2-T1)/i=%d us\n", i, T2-T1, (T2-T1)/i);

	pause();
	return 0;
}


