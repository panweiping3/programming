#include <stdio.h>
#include <unistd.h>

int main()
{
	if (lseek(STDIN_FILENO, 0, SEEK_CUR) == 1)
		printf("can't lseek\n");
	else
		printf("lseek successfully\n");

	return 0;
}
