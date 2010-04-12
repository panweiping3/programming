#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TR_SETUP 0
#define TR_WRITE 5
#define TR_RESUME 7

int addr;

int main(int argc, char *argv[])
{
    int i;
    pid_t pid;
    
    if (argc != 2) {
        printf("pls use ./a.out 0x121212\n");
        exit(0);
    }

    sscanf(argv[1], "%x", &addr);
    printf("addr=0x%x\n", addr);

    if ((pid = fork()) == 0) {
        ptrace(TR_SETUP, 0, 0, 0);
        execl("trace", "trace", 0);
        exit(1);
    }

    // wait a SIGTRAP signal
    wait((int *)0);

    for (i=0; i<32; ++i) {
        if (ptrace(TR_WRITE, pid, addr, i) == -1) {
            exit(2);
        }

        addr += sizeof(int);
    }

    ptrace(TR_RESUME, pid, 1, 0);

    return 0;
}
