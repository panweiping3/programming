#include <stdio.h>
#include <linux/unistd.h>
#include <sys/syscall.h>

#define __NR_pwp  244

int main(int argc, char** argv)
{
    printf("getpid: %d\n", getpid());
    printf("syscall pwp returns: %d\n", syscall(__NR_pwp));
    printf("syscall getpid returns: %d\n", syscall(20));
    return 0;
}
