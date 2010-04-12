#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_PASSWD_LEN		8

char *getPasswd(const char *prompt)
{
	static char buf[MAX_PASSWD_LEN + 1];	
	char *ptr = NULL;
	sigset_t sig, osig;
	struct termios ts, ots;
	FILE *fp = NULL;
	int c;
	
	if ((fp = fopen(ctermid(NULL), "r+")) == NULL)
		return NULL;
	
	setbuf(fp, NULL);
	sigemptyset(&sig);
	sigaddset(&sig, SIGINT);
	sigaddset(&sig, SIGTSTP);
	sigprocmask(SIG_BLOCK, &sig, &osig);

	tcgetattr(fileno(fp), &ts);
	ots = ts;
	ts.c_lflag &= ~(ECHO |ECHOE | ECHOK | ECHONL | ICANON);
	ts.c_oflag |= OLCUC;
	tcsetattr(fileno(fp), TCSANOW, &ts);
	fputs(prompt, fp);

	ptr = buf;
	
	while (((c = getc(fp)) != EOF) && (c != '\n'))
		if (ptr < &buf[MAX_PASSWD_LEN])
		{
			*ptr++ = c;
			fputs("*", fp);
		}

	*ptr = 0;
	putc('\n', fp);

	tcsetattr(fileno(fp), TCSANOW, &ots);
	sigprocmask(SIG_SETMASK, &osig, NULL);
	fclose(fp);
	return buf;
}

int main()
{
	char *ptr = NULL;
	
	if ((ptr = getPasswd("Enter paswd:")) == NULL)
	{
		fprintf(stderr, "get passwd error\n");
		exit(1);
	}

	fprintf(stderr, "we got passwd: %s\n", ptr);
	
	return 0;
}
