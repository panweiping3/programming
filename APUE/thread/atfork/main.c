#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;  /*初始化互斥锁*/
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;  /*初始化互斥锁*/

void prepare(void)
{
    printf("preparing locks...\n");
    pthread_mutex_lock(&lock1);
    pthread_mutex_lock(&lock2);
}

void parent(void)
{
    printf("parent unlocking locks...\n");
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
}

void child(void)
{
    printf("child unlocking locks...\n");
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
}

void *thr_fn(void *arg)
{
    printf("thread started...\n");
    pause();
    return 0;
}

int main(int argc, char *argv[])
{
    int err;
    pid_t pid;
    pthread_t tid;

    if ((err = pthread_atfork(prepare, parent, child))) {
        fprintf(stderr, "pthread_atfork error\n");
        exit(2);
    }

    err = pthread_create(&tid, NULL, thr_fn, NULL);
    if (err) {
        fprintf(stderr, "pthread_create error\n");
        exit(3);
    }

    sleep(2);

    printf("parent about to fork...\n");
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(4);
    } else  if (pid == 0) {
        printf("child returned from fork\n");
    } else {
        printf("parent returned from fork\n");
    }

    exit(0);
}
