#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int i;
	char *ptr = NULL;
	struct stat stat_buf;

	for (i=1; i<argc; i++)
	{
		fprintf(stdout, "%s ", argv[i]);
		
		if (lstat(argv[1], &stat_buf) < 0)
		{
			perror("lstat error");
			
			continue;
		}

		if ((S_ISUID & stat_buf.st_mode))
		{
			fprintf(stdout, "s uid\n");
		}
		
		if ((S_ISGID & stat_buf.st_mode))
		{
			fprintf(stdout, "s gid\n");
		}
		
		if (S_ISREG(stat_buf.st_mode) == 1)
			ptr = "regular file";
		else if (S_ISDIR(stat_buf.st_mode) == 1)
			ptr = "dirtory";		
		else if (S_ISCHR(stat_buf.st_mode) == 1)
			ptr = "character special";		
		else if (S_ISBLK(stat_buf.st_mode) == 1)
			ptr = "block special";		
		else if (S_ISFIFO(stat_buf.st_mode) == 1)
			ptr = "fifo";		
		else if (S_ISLNK(stat_buf.st_mode) == 1)
			ptr = "symbolic link";		
		else if (S_ISSOCK(stat_buf.st_mode) == 1)
			ptr = "socket";		
		else
			ptr = "**  unknown file type  **";

		fprintf(stdout, "%s\n", ptr);
	}	

	return 0;
}
