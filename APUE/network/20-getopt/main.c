#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
    int sock_fd = -1;
    int snd_buf_size = 0;
    socklen_t opt_size = sizeof(snd_buf_size);
    int ret = 0;


    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        perror("socket fail");
        goto out;
    }
    /* 获得sndbuf的长度 */
    ret = getsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, &snd_buf_size, &opt_size);
    if (ret < 0)
    {
        perror("getsockopt fail");
        printf("%d\n", errno);
        goto out;
    }
    printf("socket %d's sndbuf is %d bytes\n", sock_fd, snd_buf_size);


    /* 修改sndbuf的长度 */
    snd_buf_size = 10000;
    ret = setsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, &snd_buf_size, opt_size);
    if (ret < 0)
    {
        perror("getsockopt fail");
        printf("%d\n", errno);
        goto out;
    }


    /* 再获得sndbuf的长度 */
    ret = getsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, &snd_buf_size, &opt_size);
    if (ret < 0)
    {
        perror("getsockopt fail");
        printf("%d\n", errno);
        goto out;
    }
    printf("socket %d's sndbuf is %d bytes\n", sock_fd, snd_buf_size);
out:
    if (sock_fd >= 0)
    {
        close(sock_fd);
        sock_fd = 0;
    }
    return 0;
}
