#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct{
        char name[4];
        int age;
} people;

int main(int argc, char** argv)
{
    int shm_id;
    key_t key;
    people *shm_p;
    char* name = argv[1];
    key = ftok(name, 0);

    if(key == -1) {
        perror("ftok error");
    }
    printf("key %d\n", key);

    shm_id = shmget(key, 4096, 0);    
    if(shm_id == -1) {
        perror("shmget error");
        return 0;
    }
    printf("shm_id %d\n", shm_id);

    shm_p = (people*)shmat(shm_id, NULL, 0);
    
    int i;
    for(i = 0; i<10; i++) {
        printf("name:%s ", (shm_p + i)->name);
        printf("age: %d\n", (shm_p+i)->age);
    }

    if(shmdt(shm_p) == -1) {
        perror(" detach error ");
    }

    return 0;
}

