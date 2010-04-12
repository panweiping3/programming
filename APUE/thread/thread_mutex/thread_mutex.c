#include <stdlib.h>
#include <pthread.h>

struct foo{
	int count;
	pthread_mutex_t lock;
	int value;
};

typedef struct foo* FOO;

FOO foo_alloc(void)
{
	FOO fp;
	
	if ((fp = malloc(sizeof(FOO))) != NULL)
	{
		fp->count = 1;
		if (pthread_mutex_init(&fp->lock, NULL) != 0)
		{
			free(fp);
			return NULL;
		}
	}
	
	return fp;
}

void foo_hold(FOO fp)
{
	pthread_mutex_lock(&fp->lock);
	fp->count++;
	printf("%d is been holden\n", fp->value);
	pthread_mutex_unlock(&fp->lock);
}

void foo_release(FOO fp)
{
	pthread_mutex_lock(&fp->lock);
	
	if (--fp->count == 0)
	{
		pthread_mutex_unlock(&fp->lock);
		pthread_mutex_destroy(&fp->lock);
		printf("%d is been released\n", fp->value);
		free(fp);
	}
	else
		pthread_mutex_unlock(&fp->lock);
}

void *thread_provider()
{
	while (1)
	{
		int	i = rand();
		FOO *fp = foo_alloc();
		fp->value = i;	
	}
}

void *thread_consumer1()
{
	while (1)
	{
		int	i = rand();
		FOO *fp = foo_alloc();
		fp->value = i;	
	}
	
}

int main()
{
	int err;
	
	err = pthread_create();	
	return 0;
}
