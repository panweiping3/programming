#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char buf[MAXLINE] = {'\0'};
	
	while (fgets(buf, MAXLINE, stdin) != NULL)
		if (fputs(buf, stdout) == EOF)
		{
			fprintf(stderr, "fputs error\n");
			exit(1);
		}

	if (ferror(stdin) != 0)
	{
		fprintf(stderr, "fgets error\n");
		exit(2);
	}

	return 0;
}
