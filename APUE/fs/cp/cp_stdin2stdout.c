#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int c;
	
	while ((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF)
		{
			fprintf(stderr, "putc error\n");
			exit(1);
		}

	if (ferror(stdin) != 0)
	{
		fprintf(stderr, "getc error\n");
		exit(2);
	}

	return 0;
}
