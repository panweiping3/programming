#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int quitflag; // protected by lock
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;  /*初始化互斥锁*/
pthread_cond_t  wait = PTHREAD_COND_INITIALIZER;     /*初始化条件变量*/

void *thr_fn(void *arg)
{
    int err, signo;

    for (;;) {
        fprintf(stderr, "child thread enter main loop\n");
        err = sigwait(&mask, &signo);
        if (err) {
            fprintf(stderr, "sigwait error\n");
            exit(1);
        }

        switch (signo) {
        case SIGINT:
            printf("\ninterrupt\n");
            break;
        case SIGQUIT:
            pthread_mutex_lock(&lock);
            quitflag = 1;
            pthread_mutex_unlock(&lock);
            printf("\nquit\n");
            pthread_cond_signal(&wait);
            return (0);
        default:
            printf("unexpected signal %d\n", signo);
            exit(1);
        }
    }
}

int main(int argc, char *argv[])
{
    int err;
    sigset_t oldmask;
    pthread_t tid;
    
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);

    if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask))) {
        fprintf(stderr, "pthread_sigmask error\n");
        exit(21);
    }

    err = pthread_create(&tid, NULL, thr_fn, 0);
    if (err) {
        fprintf(stderr, "pthread_create error\n");
        exit(22);
    }

    pthread_mutex_lock(&lock);
    fprintf(stderr, "main thread enter main loop\n");

    while (quitflag == 0) {
        pthread_cond_wait(&wait, &lock);
    }
    pthread_mutex_unlock(&lock);

    quitflag = 0;
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        fprintf(stderr, "sigprocmask error\n");
        exit(23);
    }

    exit(0);
}
