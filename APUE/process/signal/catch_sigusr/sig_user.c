#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sig_user(int);

int main(int argc, char *argv[])
{
	if (signal(SIGUSR1, sig_user) == SIG_ERR){
		fprintf(stderr, "signal error\n");
		exit(1);	
	}

	if (signal(SIGUSR2, sig_user) == SIG_ERR){
		fprintf(stderr, "signal error\n");
		exit(2);	
	}
	
	while (1) {
		pause();
	}
	
	return 0;
}

void sig_user(int signo)
{
	if (signo == SIGUSR1){
		fprintf(stderr, "catch signal USR1\n");
	} else if (signo == SIGUSR2){
		fprintf(stderr, "catch signal USR2\n");
	}
	
	return;
}
