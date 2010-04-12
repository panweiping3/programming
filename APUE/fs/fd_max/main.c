#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

int main(int argc, char *argv[])
{
    long long i;
    int fd;

    fprintf(stderr, "sysconf returns:%d\n", sysconf(_SC_OPEN_MAX));
    for (i=0; i< 1024*1024*1024; ++i) {
        errno = 0;
        if ((fd = open("/dev/null", O_WRONLY)) == -1) {
            fprintf(stderr, "errno = %d, i = %lld\n", errno, i);
            perror("why open error");
            
            return 1;
        }
    }
    
    return 0;
}
