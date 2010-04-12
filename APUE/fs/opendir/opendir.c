#include <stdio.h>
#include <sys/types.h> 
#include <dirent.h>

int main(int argc, char *argv[])
{
	DIR *dir = NULL;
	if ((dir = opendir("./boot")) != NULL)
	{
		fprintf(stdout, "open ok\n");
	}
	else	
	{
		fprintf(stdout, "open error\n");
	}
	
	return 0;
}
