#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

int main(int argc, char *argv[])
{
	char line[128];
	FILE *fpin = NULL;

	if ((fpin = popen("./upper_2_lower", "r")) == NULL)
	{
		fprintf(stderr, "popen error\n");
		exit(1);
	}

	while (1)
	{
		fputs("prompt> ", stdout);
		fflush(stdout);
		
		if (fgets(line, 128, fpin) == NULL)
			break;
		
		if (fputs(line, stdout) == EOF)
		{
			fprintf(stderr, "fputs error\n");
			exit(1);
		}
	}

	if (pclose(fpin) == -1)
	{
		fprintf(stderr, "pclose error\n");
		exit(1);
	}

	putchar('\n');
	exit(0);
}


