#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// arg should be a char *
void cleanup(void *arg)
{
    printf("cleanup: %s\n", (char *)arg);
}

void *thread_f1(void *arg)
{
    printf("thread 1 start\n");
    pthread_cleanup_push(cleanup, "thread 1 first handler");
    pthread_cleanup_push(cleanup, "thread 1 second handler");
    printf("thread 1 push complete\n");

    if (arg) {
        printf("thread 1 return\n");
        return ((void *)1);
    }

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);

    return ((void *)1);
}

void *thread_f2(void *arg)
{
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup, "thread 2 first handler");
    pthread_cleanup_push(cleanup, "thread 2 second handler");
    printf("thread 2 push complete\n");

    if (arg) {
        printf("thread 2 return\n");
        pthread_exit((void *)2);
    }

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);

    pthread_exit((void *)2);
}

int main(int argc, char *argv[])
{
    int err;
    pthread_t tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, thread_f1, (void *)1);
    if (err != 0 ) {
        exit(1);
    }

    err = pthread_create(&tid2, NULL, thread_f2, (void *)1);
    if (err != 0 ) {
        exit(2);
    }

    err = pthread_join(tid1, &tret);
    if (err != 0) {
        exit(3);
    }
    printf("thread 1 exit code %d\n", (int)tret);
    
    err = pthread_join(tid2, &tret);
    if (err != 0) {
        exit(4);
    }
    printf("thread 2 exit code %d\n", (int)tret);
 
    exit(0);
}
