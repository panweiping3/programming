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
    char *p;
    pid_t pid;

    msgid = msgget(MSGKEY, 0777);

    pid = getpid();
    printf("pid %d\n", pid);

    p = msg.mtext;
    for (i=0; i<26; ++i) {
        *p++ = 'a' + i;
    }
    msg.mtype = pid;

    msgsnd(msgid, &msg, sizeof(int), 0);
    msgrcv(msgid, &msg, 256, 0, 0);

    for (i=0; i<26; ++i) {
        printf("msg[%d]=%c\n", i, msg.mtext[i]);
    }

    return 0;
}

