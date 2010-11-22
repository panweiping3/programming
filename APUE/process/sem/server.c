#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#include "sem.h"

#define READTIME 1
int main()
{
    key_t key;
    int shmid, semid;
    char *shm_p;
    char msg[7] = "-data-";
    struct semid_ds buf;

    key = ftok("/", 0);
    shmid = shmget(key, SEGSIZE, IPC_CREAT|0666);
    if (-1 == shmid){
        printf(" create shared memory error\n");
        return -1;
    }

    shm_p = (char *)shmat(shmid, NULL, 0);
    if (-1 == (int)shm_p){
        printf(" attach shared memory error\n");
        return -1;
    }

    semid = sem_creat(key);

    char i;
//    for (i = 0;i <= 3;i++){
	while (1) {
		p(semid);
		fprintf(stderr, "%s %d %s :server lock\n", __FILE__, __LINE__, __func__);	
		
		sleep (3);
		v(semid);
		fprintf(stderr, "%s %d %s :server unlock\n", __FILE__, __LINE__, __func__);	
		/*
        sleep(1);
        p(semid);
			fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);	
        sleep(READTIME);
        msg[5] = '0' + i;
        memcpy(shm_p, msg, sizeof(msg));
        sleep(3);
		*/
//        v(semid);
    }

    shmdt(shm_p);
    shmctl(shmid, IPC_RMID, &buf);
    del_sem(semid);
    return 0;
}
