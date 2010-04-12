#include <fcntl.h>



int main(void)
{
	int fd;
	pid_t pid;
	
	if ((fd = creat("tmplock", FILE_MODE)) < 0)
		printf("create tmplock failed\n");
	
	if (write(fd, "ab", 2) != 2)
		printf("create tmplock failed\n");

	if ((pid = fork()) < 0)
		printf("create tmplock failed\n");
	else if (pid == 0)
		{
			

		}
		
}
