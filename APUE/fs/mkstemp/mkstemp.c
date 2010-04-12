#include <stdio.h>
#include <stdlib.h>

int main()
{
	char temp[] = "/tmp/foo.XXXXXX";

    if (mkstemp(temp) == -1)
	{
        fprintf(stderr, "Make temporary directory failed.\n");
        return -1;
    }

	return 0;
}
