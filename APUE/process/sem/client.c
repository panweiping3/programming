#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <time.h>
#include <sys/ipc.h>

#include "sem.h"

#define READTIME 1

// 打印程序执行时间
void out_time(void)
{
    static long start = 0;
    time_t tm;
    if (0 == start){
        tm = time(NULL);
        start = (long)tm;
        printf(" now start ...\n");
		return;
    }

    printf(" second: %ld \n", (long)(time(NULL)) - start);
}

//等待信号量变成0
int main(void)
{
    key_t key;
    int shmid, semid;
    char *shm_p;
    char msg[100];
    char i;

    key = ftok("/", 0);
    shmid = shmget(key, SEGSIZE, 0);

    if(-1 == shmid){
        printf(" create shared memory error\n");
        return -1;
    }

    shm_p = (char *)shmat(shmid, 0, 0); 
    if (-1 == (int)shm_p){
        printf(" attach shared memory error\n");
        return -1;
    }
    
    semid = get_sem(key);
//    for (i = 0;i < 10;i ++){
	while (1) {
		p(semid);
		fprintf(stderr, "%s %d %s :client lock\n", __FILE__, __LINE__, __func__);	
		sleep(10);
		v(semid);
		fprintf(stderr, "%s %d %s :client unlock\n", __FILE__, __LINE__, __func__);	

//        sleep(2);
// 		  wait_zero(semid);
//        v(semid);
//        printf("Message geted is: %s \n", shm_p + 1);
//        out_time();
    }

    shmdt(shm_p);
    return 0;
}
