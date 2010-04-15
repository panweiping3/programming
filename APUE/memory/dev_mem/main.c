#include <stdio.h>
#include <fcntl.h>

#define NUM 10

int main(void)
{
    int fd;
    char rdbuf[NUM];
    char wrbuf[NUM] = "butterfly";
    int i;

    fd = open("/dev/mem",O_RDWR);
    if(fd < 0) {
        printf("open /dev/mem failed.");
    }

    read(fd, rdbuf, NUM);
    for(i = 0;i < NUM;i++) {
        printf("old mem[%d]:%c\n", i, *(rdbuf + i));
    }

    lseek(fd, 0, SEEK_SET);
    write(fd, wrbuf, NUM);
    lseek(fd, 0, SEEK_SET);
    read(fd, rdbuf, NUM);

    for(i = 0;i < NUM;i++) {
        printf("new mem[%d]:%c\n",i,*(rdbuf + i));
    }

    return 0;
}
