#include <stdio.h>

int main()
{
	long c1 = 2147483647;
	unsigned long c2 = 20;

	// 对比一下以下代码
	//long c2 = 20;
	long long c3 = c1 + c2;

	printf("sizeof(long) %d\n", sizeof(long));
	printf("c1=%ld\n", c1);
	printf("c2=%ld\n", c2);
	printf("c3=%lld\n", c3);
	return 0;
}
