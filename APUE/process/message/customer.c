#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY  75

struct msgform {
    long mtype;
    char mtext[256];
};

int main(int argc, char *argv[])
{
    struct msgform msg;
    int msgid, i;
    int *p;
    pid_t pid;

    msgid = msgget(MSGKEY, 0777);

    pid = getpid();
    printf("client pid %d\n", pid);

    p = (int *)msg.mtext;
    *p = pid;
    msg.mtype = 1;

    msgsnd(msgid, &msg, sizeof(int), 0);
    msgrcv(msgid, &msg, 256, pid, 0);
    printf("client: receive message from pid %d\n", *p);

    return 0;
}

