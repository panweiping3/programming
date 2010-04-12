#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
// FIBMAP is defined in linux/fs.h

int main(int argc, char *argv[])
{
    unsigned long long block = 0;
    int fd;
    int i;

    if (argc != 2) {
        fprintf(stderr, "use ./fibmap file\n");
        fprintf(stderr, "we need root permission\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "block %lld\n", block);
        exit(1);
    }
    
    errno = 0;
    if (ioctl(fd, FIBMAP, &block) == -1) {
        fprintf(stderr, "ioctl error :%s\n", strerror(errno));
        exit(1);
    }

    fprintf(stderr, "block %lld\n", block);
    return 0;
}
