#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "arguments incorrect\n");
		fprintf(stderr, "./a.out aaa\n");
		exit(1);
	}	

	if (access(argv[1], R_OK) == 0)
		fprintf(stdout, "read ok\n");

	if (access(argv[1], W_OK) == 0)
		fprintf(stdout, "write ok\n");

	if (access(argv[1], X_OK) == 0)
		fprintf(stdout, "exexute ok\n");

	if (access(argv[1], F_OK) == 0)
		fprintf(stdout, "exist ok\n");

	return 0;
}
