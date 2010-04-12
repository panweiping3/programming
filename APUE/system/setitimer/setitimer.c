#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void sig_alarm_handler(int sig);

int main()
{
	struct itimerval expire_time;
	
	signal(SIGALRM, sig_alarm_handler);
	
	expire_time.it_interval.tv_sec = 3;
	expire_time.it_interval.tv_usec = 0;
	expire_time.it_value.tv_sec = 3;
	expire_time.it_value.tv_usec = 0;

	if (setitimer(ITIMER_REAL, &expire_time, NULL) < 0)
	{
		perror("setitimer ITIMER_REAL error");
		exit(1);
	}
		
	while (1)
		pause();

}

void sig_alarm_handler(int sig)
{
	printf("signal SIGALRM happens\n");	

	return;
}



