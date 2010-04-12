#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  /*初始化互斥锁*/
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;     /*初始化条件变量*/

void *thread1(void *);
void *thread2(void *);

int g_i=1;

int main(void)
{
    pthread_t t_a;
    pthread_t t_b;

    pthread_create(&t_a, NULL, thread2, (void *)NULL);/*创建进程t_a*/
    pthread_create(&t_b, NULL, thread1, (void *)NULL); /*创建进程t_b*/
    
    pthread_join(t_a, NULL);    /*等待进程t_b结束*/
    pthread_join(t_b, NULL);    /*等待进程t_b结束*/
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    exit(0);
}

void *thread1(void *arg)
{
    for(g_i=1; g_i <= 9; g_i++)
    {
        pthread_mutex_lock(&mutex);         /*锁住互斥量*/
        if (g_i % 2 == 0) {
            pthread_cond_signal(&cond);         /*条件改变，发送信号，通知t_b进程*/
        }
        pthread_mutex_unlock(&mutex);/*解锁互斥量*/
        sleep(1);
    }

    return NULL;
}

void *thread2(void *arg)
{
    while(g_i < 9)
    {
        pthread_mutex_lock(&mutex);
        
        if(g_i % 2 != 0) {
            pthread_cond_wait(&cond,&mutex);/*等待*/
        }
        fprintf(stderr, "thread2:    %d\n", g_i);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}
