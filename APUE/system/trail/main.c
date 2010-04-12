#include <unistd.h>
#include <fcntl.h>
int main()
{
    int fd;
    char buf[512];

    fd = open("/dev/sda", O_RDONLY);
    
    if (fd >= 0) {
        read(fd, buf, sizeof(buf));
    }

    return 0;
}

