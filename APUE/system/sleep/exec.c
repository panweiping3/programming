#include <stdio.h>
#include <unistd.h>

int main()
{
    int status;
    pid_t pid;

    if ((pid = fork()) < 0) {
        status = -1;
    } else if (pid == 0) {
        execl("./sleep", NULL);
        _exit(127);
    } else {
        if(waitpid(pid, &status, 0) < 0) {
            status = -1;
        }
    }

    return status;
}

