#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

extern const char * const sys_siglist[];

int main(int argc, char *argv[])
{
    int i;

    for (i = 0; i < 32; ++i){
		fprintf(stderr, "signal %d:%s\n", i, strsignal(i));
		fprintf(stderr, "signal %d:%s\n", i, sys_siglist[i]);
    }
	return 0;
}

