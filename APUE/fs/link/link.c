#include <stdio.h>

int main()
{
	if (unlink("./cp") != 0)
	{
		perror("ulink error");
		
		return -1;
	}

	return 0;
}
