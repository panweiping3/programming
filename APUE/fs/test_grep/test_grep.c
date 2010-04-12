#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void match(char *file_name, char *pattern);

int main(int argc, char *argv[])
{
	DIR *dir_p = NULL;
	struct dirent *dirent_p = NULL;

	if ((dir_p = opendir("./")) == NULL)
	{
		fprintf(stderr, "open dir current dir error\n");
		exit(1);
	}
	
	while ((dirent_p = readdir(dir_p)) != NULL)
	{
		struct stat stat_buf;

		if ((strcmp(dirent_p->d_name, ".") == 0) || (strcmp(dirent_p->d_name, "..") == 0))
			continue;
		
		if (lstat(dirent_p->d_name, &stat_buf) < 0)
			continue;

		if (S_ISREG(stat_buf.st_mode) == 1)	
			match(dirent_p->d_name, argv[1]);
	}

	closedir(dir_p);
	return 0;
}

void match(char *file_name, char *pattern)
{
	int i = 0;
	FILE *fp = NULL;
	char line[256] = {'\0'};

	if ((fp = fopen(file_name, "r")) == NULL)
		return ;
	
	while (!feof(fp))
	{
		i++;
		fgets(line, 256, fp);

		if (strstr(line, pattern) != NULL)
		{
			fprintf(stdout, "%s: %d: %s", file_name, i, line);
			continue;
		}
	}

	fclose(fp);
	
	return;
}
