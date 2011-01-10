#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// The distance mod 32768 between two pids, where the first pid is expected
// to be smaller than the second.
int PidDistance(pid_t first, pid_t second) 
{
    return (second + 32768 - first) % 32768;
}

int main(int argc, char* argv[]) 
{

    int failed = 0;
    pid_t last_pid = 0;
    int i;
    for (i = 0; i < 10000000; ++i) {
        if (i % 32768 == 0)
            printf("Iter: %d\n", i/32768);
            int child_exit_code = i % 256;
            pid_t pid = fork();

            if (pid == -1) {
                fprintf(stderr, "fork failed, iteration %d, errno=%d", i, errno);
                exit(1);
            }

            if (pid == 0) {
                // Child
                exit(child_exit_code);
            } else {
                // Parent
                if (i > 0) {
                    int distance = PidDistance(last_pid, pid);
                    if (distance == 0 || distance > 30000) {
                        fprintf(stderr, 
                                "Unexpected pid sequence: previous fork: pid=%d, "
                                "current fork: pid=%d for iteration=%d.\n",
                                last_pid, 
                                pid, 
                                i);
                                    
                        failed = 1;
                    }
                }
                last_pid = pid;
                int status;
                int reaped = wait(&status);
                if (reaped != pid) {
                    fprintf(stderr, 
                            "Wait return value: expected pid=%d, "
                            "got %d, iteration %d\n",
                            pid, reaped, i);
                    failed = 1;
                } else if (WEXITSTATUS(status) != child_exit_code) {
                    fprintf(stderr,
                            "Unexpected exit status %x, iteration %d\n",
                            WEXITSTATUS(status), i);
                    failed = 1;
                }
            }
    }

    exit(failed);
}

