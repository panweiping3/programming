#include <stdio.h>

int main()
{
	printf("sizeof(long) %d\n", sizeof(long));

	long c1 = 2147483647;
	long c2 = 20;
	long c3 = c1 + c2; //溢出
	printf("c1=%ld\n", c1);
	printf("c2=%ld\n", c2);
	printf("c3=%ld\n", c3);

	long cc1 = 2147483647;
	long cc2 = 20;
	unsigned long cc3 = cc1 + cc2; //不溢出
	//这说明，long 在计算过程中，如果可以提升为unsigned long，则会提升
	printf("cc1=%ld\n", cc1);
	printf("cc2=%ld\n", cc2);
	printf("cc3=%lu\n", cc3);

	long ccc1 = 2147483647;
	long ccc2 = 4;
	unsigned long ccc3 = ccc1 * ccc2; 
	printf("ccc1=%ld\n", ccc1);
	printf("ccc2=%ld\n", ccc2);
	printf("ccc3=%lu\n", ccc3);

	return 0;
}
