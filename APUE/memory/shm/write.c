/***** testwrite.c *******/
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct{
    char name[4];
    int age;
} people;

int main(int argc, char **argv)
{
    key_t key;
    int shm_id;
    void *shm_p = NULL;
    char *name = argv[1];

    key = ftok(name, 0);
    if(key == -1) {
        perror("ftok error");
    }
    printf("key %lx\n", key);

    shm_id = shmget(key, 4096, IPC_CREAT|0604);  
    if(shm_id == -1){
        perror("shmget error");
        return;
    }
    printf("shm_id %d\n", shm_id);

    shm_p = shmat(shm_id, NULL, 0666);
    printf("p address %x\n", shm_p);

    char temp;
    temp='a';
    people *people_p = NULL;
    int i;
    for(i=0; i<10; i++){
        temp += 1;
        people_p = (people *)shm_p + i;
        memcpy(people_p->name, &temp, 1);
        people_p->age = 20 + i;
    }
    
    if(shmdt((void *)shm_p) == -1) {
        perror(" detach error ");
    }

    return 0; 
}

