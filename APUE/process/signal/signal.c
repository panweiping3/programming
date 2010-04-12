#include <stdio.h>
#include <signal.h>

void haha()
{
	printf("I am killed!");
}


int main()
{
	signal(SIGSTOP, haha);
	signal(SIGKILL, haha);

	pause();
}
