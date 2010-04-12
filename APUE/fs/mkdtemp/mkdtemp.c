#include <stdio.h>
#include <stdlib.h>

int main()
{
	char temp[] = "/tmp/foo.XXXXXX";

    char *dir = mkdtemp(temp);

    if (dir == NULL)
	{
        fprintf(stderr, "Make temporary directory failed.\n");
        return -1;
    }

	return 0;
}
