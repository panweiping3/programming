#include <stdio.h>
#include <stdlib.h>

typedef void (*FUN)();
FUN fun[2];

void loop()
{
	int i;
	for (;;) {
		for (i = 0; i < 2; i++) {
			fun[i]();
		}
		sleep(1);
	}
}

void test1()
{
	printf("test1\n");
}


void test2(int a)
{
	printf("test2: %d\n", a);
}

int main()
{
	fun[0] = test1;
	fun[1] = test2;
	loop();
}

