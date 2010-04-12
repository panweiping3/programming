#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TASK_NUM 10

struct task{
    int id;
    int time;
};

struct task *tasks[TASK_NUM];

int init_tasks(void)
{
    int i;
    struct task *task_p;
    
    printf("init_tasks start\n");
    for (i=0; i<TASK_NUM; ++i) {
        task_p = (struct task *)malloc(sizeof(struct task));
        if (task_p) {
            int time = rand() % 10; 
            task_p->id = i;
            task_p->time = time;
            tasks[i] = task_p;
            task_p = NULL;
        } else {
            return 1;
        }
    }
    printf("init_tasks end\n");
    
    return 0;
}

void *thread0(void *arg)
{
    printf("thread0 receive a task\n");
    struct task *task_p = (struct task *)arg;
    if (task_p) {
        sleep(task_p->time);
        printf("%d thread has finished, waste thread0 %d seconds\n", task_p->id, task_p->time);
    }
}

void *thread1(void *arg)
{
    printf("thread1 receive a task\n");
    struct task *task_p = (struct task *)arg;
    if (task_p) {
        sleep(task_p->time);
        printf("%d thread has finished, waste thread1 %d seconds\n", task_p->id, task_p->time);
    }
}

void *thread2(void *arg)
{
    printf("thread2 receive a task\n");
    struct task *task_p = (struct task *)arg;
    if (task_p) {
        sleep(task_p->time);
        printf("%d thread has finished, waste thead2 %d seconds\n", task_p->id, task_p->time);
    }
}


int main(int argc, char *argv[])
{
    int i;
    pthread_t thread_id0 = 0;
    pthread_t thread_id1 = 0;
    pthread_t thread_id2 = 0;

    if (init_tasks() != 0) {
        return -1;
    }

    for (i=0; i<TASK_NUM; ++i) {
        int r = rand() % 3;
        printf("I'll wait %d seconds to divide a task\n", r);
        sleep(r);
        
        switch (r) {
        case 0: 
                if (thread_id0) {
                    pthread_join(thread_id0, NULL);
                    thread_id0 = 0;
                }
                if ((thread_id0 = pthread_create(&thread_id0, NULL, thread0, tasks[i])) != 0) {
                    exit(2);
                }
                break;
        case 1: 
                if (thread_id1) {
                    pthread_join(thread_id1, NULL);
                    thread_id1 = 0;
                }
                if ((thread_id1 = pthread_create(&thread_id1, NULL, thread1, tasks[i])) != 0) {
                    exit(2);
                }
                break;
        case 2: 
                if (thread_id2) {
                    pthread_join(thread_id2, NULL);
                    thread_id2 = 0;
                }
                if ((thread_id2 = pthread_create(&thread_id2, NULL, thread2, tasks[i])) != 0) {
                    exit(2);
                }
                break;
        default:
                break;
        }
    }

    if (thread_id0) {
        pthread_join(thread_id0, NULL);
    }
    if (thread_id1) {
        pthread_join(thread_id1, NULL);
    }
    if (thread_id2) {
        pthread_join(thread_id2, NULL);
    }
    printf("divide_tasks finished\n");

    return 0;
}
