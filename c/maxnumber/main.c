#include <stdio.h>

int main()
{
#if 0
	int a1 = 1, a2 = 0;
	printf("sizeof int:%d\n", sizeof(a1));
	
	while (a2 < a1) {
		a2 = a1;
		a1++;
	}

	printf("a1=%d\n", a1);
	printf("a2=%d\n", a2);

	long b1 = 1, b2 = 0;
	printf("sizeof long:%d\n", sizeof(b1));
	
	while (b2 < b1) {
		b2 = b1;
		b1++;
	}

	printf("b1=%ld\n", b1);
	printf("b2=%ld\n", b2);
#endif	
	long long c1 = 429496721, c2 = 429496720;
	printf("sizeof long long:%d\n", sizeof(c1));
	
	while (c2 < c1) {
		c2 = c1;
		c1 += 1;
	}

	printf("c1=%lld\n", c1);
	printf("c2=%lld\n", c2);
	return 0;
}
