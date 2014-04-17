#include <stdio.h>
int main(void)
{
	for (;;) {
		int i = 10;
		fprintf(stderr, "%s %d %s i=%d\n", __FILE__, __LINE__, __func__, i);
		i++;
	}
	return 0;
}
