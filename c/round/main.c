#include <stdio.h>

int round64(int i)
{
	return (i + 63) & ~63;
}

int main()
{
	int i = 0;
	for (i=0; i<100; ++i) {
		printf ("i=%d, round(i)=%d\n", i, round64(i));
	}

	return 0;
}
