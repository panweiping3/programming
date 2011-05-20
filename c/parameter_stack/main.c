/*
 * 函数参数自右至左入栈，
 * 支持变长参数
 */

#include <stdio.h>

void foo(int x, int y, int z)
{
	printf("x = %d at [%X]\n", x, &x);
	printf("y = %d at [%X]\n", y, &y);
	printf("z = %d at [%X]\n", z, &z);
}

int main(int argc, char *argv[])
{
	foo(100, 200, 300);
	return 0;
}
