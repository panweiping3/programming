#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#ifdef _POSIX_THREADS
#define SUPPORT 1
#else
#define SUPPORT 0
#endif

int main(int argc, char *argv[])
{
    if (sysconf(_SC_THREADS) != -1) {
        printf("pthread is supported 1\n");
    }

    if (SUPPORT) {
        printf("pthread is supported 2\n");
    }

    printf("thread is %u\n", pthread_self());

    return 0;
}
