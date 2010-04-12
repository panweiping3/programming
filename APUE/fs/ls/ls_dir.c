#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	DIR *dir_p = NULL;
	struct dirent *dirent_p = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "bad command! ./a.out dir\n");
		exit(1);
	}
	
	if ((dir_p = opendir(argv[1])) == NULL)
	{
		fprintf(stderr, "open dir %s error\n", argv[1]);
		exit(2);
	}

	while ((dirent_p = readdir(dir_p)) != NULL)
		fprintf(stdout, "%s\n", dirent_p->d_name);

	closedir(dir_p);
	
	return 0;
}
