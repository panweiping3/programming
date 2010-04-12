#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_alarm_handler(int sig);

int main()
{
	signal(SIGALRM, sig_alarm_handler);
	alarm(3);
	
	while(1) 
	{
		sleep(10);
	}
}

void sig_alarm_handler(int sig)
{
	printf("alarming\n");
	return;
}
