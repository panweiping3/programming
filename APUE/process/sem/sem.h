#include <sys/sem.h>
#include <sys/ipc.h>

#define SEGSIZE 1024

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

//创建信号量
int sem_creat(key_t key)
{
    union semun sem;
    int semid;
    sem.val = 0;
    semid = semget(key, 1, IPC_CREAT | 0666);
    if (-1 == semid){
        printf("create semaphore error\n");
        exit(-1);
    }    
    
    semctl(semid, 0, SETVAL, sem);
    return semid;
}

//获取信号量
int get_sem(key_t key)
{
    union semun sem;
    int semid;
    sem.val = 0;
    semid = semget(key, 0, 0);
    if (-1 ==  semid){
        printf("create semaphore error\n");
        exit(-1);
    }

    return semid;
}

//删除信号量
void del_sem(int semid)
{
    union semun sem;
    sem.val = 0;
    semctl(semid, 0, IPC_RMID, sem);
}

//p
int p(int semid)
{
    struct sembuf sops={0, +1, IPC_NOWAIT};
    return (semop(semid, &sops, 1));
}

//v
int v(int semid)
{
    struct sembuf sops={0, -1, IPC_NOWAIT};
    return (semop(semid, &sops, 1));
}

void wait_zero(int semid)
{
    struct sembuf sops={0, 0, 0};
    semop(semid, &sops, 1);
}
