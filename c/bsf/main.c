#include <stdio.h>
static inline unsigned long ffz(unsigned long word)
{
	asm("bsf %1,%0"
    	: "=r" (word)
    	: "r" (word));
	return word;
}

int main()
{
	unsigned long num = 0;
	printf("num=%lu, num=0x%x, ffz(num)=%lu\n", num, num, ffz(num));

	num = 1;
	printf("num=%lu, num=0x%x, ffz(num)=%lu\n", num, num, ffz(num));
	
	num = 2;
	printf("num=%lu, num=0x%x, ffz(num)=%lu\n", num, num, ffz(num));

	num = 64;
	printf("num=%lu, num=0x%x, ffz(num)=%lu\n", num, num, ffz(num));

	num = 0774;
	printf("num=%lu, num=0x%x, ffz(num)=%lu\n", num, num, ffz(num));

	num = 0xe;
	printf("num=%lu, num=0x%x, ffz(num)=%lu\n", num, num, ffz(num));

	num = 0xffffffff;
	printf("num=%lu, num=0x%x, ffz(num)=%lu\n", num, num, ffz(num));

	return 0;
}
