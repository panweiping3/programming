#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY  75

struct msgform {
    long mtype;
    char mtext[256];
};

int msgid;
void cleanup()
{
    msgctl(msgid, IPC_RMID, 0);
    exit(0);
}

int main(int argc, char *argv[])
{
    struct msgform msg;
    int i, *p;
    pid_t pid;
    
    printf("server pid is %d\n", getpid());
    
    for (i=0; i<20; ++i) {
        signal(i, cleanup);
    }

    msgid = msgget(MSGKEY, 0777|IPC_CREAT);

    for (;;) {
        msgrcv(msgid, &msg, 256, 1, 0);
        p = (int *)msg.mtext;
        pid = *p;
        printf("server: receive data from pid %d\n", pid);
        msg.mtype = pid;
        *p = getpid();
        msgsnd(msgid, &msg, sizeof(int), 0);
    }
    return 0;
}

