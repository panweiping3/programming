#include <stdio.h>
#include <unistd.h>

int main()
{
	char *const argv [] = {"ls", "-l", NULL};
	if (fork() ==0 )
		execve("/bin/ls", argv, NULL);
	else
		getchar();

    return 0;
}
