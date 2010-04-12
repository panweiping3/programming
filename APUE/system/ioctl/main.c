#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
           
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

//int ioctl(int d, int request, ...);

//#define BLKRRPART _IO(0X12, 95)

int main(int argc, char *argv[])
{
    int fd;
    int ret = 0;
    fd = open("/dev/sdb", O_RDWR);
    
    if (fd == -1) {
        fprintf(stderr, "open error\n");
        exit (1);
    } else {
        fprintf(stderr, "open ok\n");
    }
    
    errno = 0;
    if ((ret = ioctl(fd, BLKRRPART)) != 0) {
        fprintf(stderr, "ioctl error:%d\n", ret);
        perror("error:\n");
        exit (2);
    } else {
        fprintf(stderr, "ioctl ok:%d\n", ret);
    }

    close(fd);
}
