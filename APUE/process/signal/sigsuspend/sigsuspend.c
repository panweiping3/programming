#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sig_int(int);

int main(int argc, char *argv[])
{
    sigset_t old_sig_mask, new_sig_mask, wait_mask;

    if (signal(SIGINT, sig_int) == SIG_ERR) {
		fprintf(stderr, "signal error\n");
        exit(1);
    }

    sigemptyset(&wait_mask);
    sigaddset(&wait_mask, SIGUSR1);
    sigemptyset(&new_sig_mask);
    sigaddset(&new_sig_mask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &new_sig_mask, &old_sig_mask) < 0) {
		fprintf(stderr, "sigprocmask error\n");
        exit(2);
    }

    /*
     * critical area start
     */
    
    sleep(10);

    /*
     * critical area start
     */

    if (sigsuspend(&wait_mask) != -1) {
		fprintf(stderr, "sigsuspend error\n");
        exit(3);
    }

    if (sigprocmask(SIG_SETMASK, &old_sig_mask, NULL) < 0) {
		fprintf(stderr, "sigprocmask error\n");
        exit(4);
    }

	return 0;
}

static void sig_int(int signo)
{
    fprintf(stderr, "catch signal SIGINT\n");
	return;
}
