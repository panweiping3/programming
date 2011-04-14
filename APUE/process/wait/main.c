#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    fprintf(stderr, "%s %d %s I'm parent=%d\n", __FILE__, __LINE__, __func__, getpid());   
    if ((pid = fork()) < 0) {
        fprintf(stderr, "%s %d %s fork error\n", __FILE__, __LINE__, __func__);   
        return 1;
    } else if (pid == 0) {
        fprintf(stderr, "%s %d %s I'm child=%d\n", __FILE__, __LINE__, __func__, getpid());   
        sleep(120);
        fprintf(stderr, "%s %d %s child exited\n", __FILE__, __LINE__, __func__);   
        exit(4); 
    } else {
        fprintf(stderr, "%s %d %s I'm parent\n", __FILE__, __LINE__, __func__);   
        sleep(120);
        int status;
        if (waitpid(pid, &status, 0) <= 0) {
            fprintf(stderr, "%s %d %s parent waitpid error\n", __FILE__, __LINE__, __func__);   
            return 2;
        } else {
            fprintf(stderr, "%s %d %s parent waitpid ok\n", __FILE__, __LINE__, __func__);   
            fprintf(stderr, "%s %d %s parent waitpid status=%d\n", __FILE__, __LINE__, __func__, status);   
        }
    }
    
    return 0;
}
