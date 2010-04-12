#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>


static pid_t *childpid = NULL;

//static int maxfd = OPEN_MAX;
static int maxfd = NR_OPEN;

FILE *popen(const char *cmdstring, const char *type)
{
    int i;
    int pfd[2];
    pid_t pid;
    FILE *fp;

    if (((*type) != 'r') && ((*type) != 'w')) {
        errno = EINVAL;
        return NULL;
    }

    if (!childpid) {
        if ((childpid = calloc(maxfd, sizeof(pid_t))) == NULL) {
           return NULL; 
        }
    }

    if (pipe(pfd) < 0) {
        return NULL;
    }

    if ((pid = fork()) < 0) {
        return NULL;
    } else if (pid == 0) {
        if ((*type) == 'r') {
            close(pfd[0]);
            if (pfd[1] != STDOUT_FILENO) {
                dup2(pfd[1], STDOUT_FILENO);
                close(pfd[1]);
            }
        } else {
            close(pfd[1]);
            if (pfd[0] != STDIN_FILENO) {
                dup2(pfd[0], STDIN_FILENO);
                close(pfd[0]);
            }
        }
    
        for (i = 0; i < maxfd; ++i) {
            if (childpid[i] > 0) {
                close(i);
            }
        }

        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127);
    }
    
    if ((*type) == 'r') {
        close(pfd[1]);
        if ((fp = fdopen(pfd[0], type)) == NULL) {
            return NULL;
        }
    } else {
        close(pfd[0]);
        if ((fp = fdopen(pfd[1], type)) == NULL) {
            return NULL;
        }
    }
    
    childpid[fileno(fp)] = pid;
    return fp;
}

int pclose(FILE *fp)
{
    int fd, stat;
    pid_t pid;

    if (!childpid) {
        errno = EINVAL;
        return (-1);
    }
    
    fd = fileno(fp);
    if ((pid = childpid[fd]) == 0) {
       errno = EINVAL;
       return (-1);
    }

    childpid[fd] = 0;
    if (fclose(fp) == EOF) {
        return (-1);
    }

    while (waitpid(pid, &stat, 0) < 0) {
        if (errno != EINVAL) {
            return (-1);
        }
    }

    return (stat);
}
