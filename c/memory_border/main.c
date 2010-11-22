#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *p = NULL;
	p = malloc(((1L << 30 + 1L << 31) + 1000));
	printf("%x\n", p);
	return 0;
}
