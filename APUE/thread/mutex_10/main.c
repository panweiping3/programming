#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void *thread(void *arg)
{
    while(1) {
        pthread_mutex_lock(&mutex);
        printf("pthread:%d %ld\n", (int)arg, pthread_self());
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }

    pthread_exit(NULL);
}

int main(void)
{
    int             i;
    pthread_t     pid[10];

      
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 10; i++) {
        pthread_create( pid + i, NULL, thread, (void*)i);
    }
    
    while(1)
        ;

    return 0;
        
}
