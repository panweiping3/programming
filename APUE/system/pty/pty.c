#include <stdio.h>
#include <termios.h> 
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif

#ifdef LINUX
#define OPTSTR "+d:einv"
#else
#define OPTSTR "d:einv"
#endif

static void set_noecho(int);
void do_driver(char *);
void loop(int, int);

int main(int argc, char *argv[])
{
	int fdm, c, ignoreeof, interative, noecho, verbose;
	pid_t pid;
	char *driver = NULL;
	char slave_name[20];
	struct termios orig_termios;
	struct winsize size;
	
	interative = isatty(STDIN_FILENO);
	ignoreeof = 0;
	noecho = 0;
	verbose = 0;
	driver = NULL;

	opterr = 0;
	
	while ((c = getopt(argc, argv, OPTSTR)) != EOF)
	{
		switch (c)
		{
			case 'd':
				driver = optarg;
				break;
			case 'e':
				noecho = 1;
				break;
			case 'i':
				ignoreeof = 1;
				break;
			case 'n':
				interative = 0;
				break;
			case 'v':
				verbose = 1;
				break;
			case '?':
				exit(1);
		}
	}
	
	if (optind >= argc)
	{
		fprintf(stderr, "argc error\n");
		exit(1);
	}	
	
	if (interative)
	{
		if (tcgetattr(STDIN_FILENO, &orig_termios) < 0)
		{
			fprintf(stderr, "tcgetattr error\n");
			exit(1);
		}

		if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char *)&size) < 0)
		{
			fprintf(stderr, "ioctl error\n");
			exit(1);
		}
	
		pid = pty_fork();
	}

}
