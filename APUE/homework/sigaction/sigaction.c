#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

void new_segv_handler(int signal);

jmp_buf env;

int main()
{
    struct sigaction new, old;

	new.sa_handler = new_segv_handler;

	if (sigaction(SIGSEGV, &new, &old) == -1)
	{
		fprintf(stderr, "set new SIGSEGV handler error\n");
		return 1;
	}

	fprintf(stdout, "change SIGSEGV handler successfully\n");

	if (setjmp(env) == 0)
	{
	    char *p = NULL;
		*p = 1;			//It will cause SIGSEGV
	}
	else
	{
		if (sigaction(SIGSEGV, &old, NULL) == -1)
		{
			fprintf(stderr, "restore old SIGSEGV handler error\n");
			return 2;
		}
	}

	fprintf(stdout, "restore old SIGSEGV handler successfully\n");
	
	return 0;
}

void new_segv_handler(int signal)
{
	fprintf(stdout, "I'm in new SIGSEGV handler\n");
	longjmp(env, 1);	
	return;
}
