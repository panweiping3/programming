#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int newfd;
    printf("STDOUT_FILENO = %d\n", STDOUT_FILENO);

    newfd = dup(STDIN_FILENO);
    printf("newfd = %d\n", newfd);

    newfd = open("/dev/null", O_RDONLY); 
    printf("/dev/null = %d\n", newfd);

    // dup2 will close STDOUT_FILENO first
    newfd = dup2(newfd, STDOUT_FILENO);

    printf("newfd = %d\n", newfd);

    fprintf(stdout, "stdout STDOUT_FILENO was closed by dup2()\n");

    fprintf(stderr, "stderr STDOUT_FILENO was closed by dup2()\n");

    return 0;
}
