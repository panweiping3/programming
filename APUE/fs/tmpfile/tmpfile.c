#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1024

int main()
{
	char name[L_tmpnam], line[MAXLINE];
	FILE *fp = NULL;

	printf("%s\n", tmpnam(NULL));
	
	tmpnam(name);
	printf("%s\n", tmpnam(NULL));
	
	if ((fp = tmpfile()) == NULL)
	{
		perror("create tmp file error");
		exit(1);
	}	 

	fputs("One line of output\n", fp);
	
	rewind(fp);

	if (fgets(line, sizeof(line), fp) == NULL)
	{
		perror("fgets error");
		exit(2);
	}	
	
	fputs(line, stdout);

	return 0;
}
