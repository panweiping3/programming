#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    register int i;

    setpgrp();
    fprintf(stderr, "parent pid=%d, pgrp=%d\n", getpid(), getpgrp());

    for (i=0; i<10; ++i) {
        if (fork() == 0) {
            // in child
            if (i & 1) {
                setpgrp();
            }

            fprintf(stderr, "pid=%d, pgrp=%d\n", getpid(), getpgrp());
            pause();
        }
    }

    // in parent
    kill(0, SIGINT);

    return 0;
}
