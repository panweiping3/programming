#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

int main(int argc, char *argv[])
{
	int c;
	
	while ((c = getchar()) != EOF)
	{
		if (isupper(c))
			c = tolower(c);
		
		if (putchar(c) == EOF)
		{
			fprintf(stderr, "EOF\n");
			exit(1);
		}

		if (c == '\n')
			fflush(stdout);
	}

	exit(0);
}


