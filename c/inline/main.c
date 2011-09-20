#include <stdio.h>

static inline void f(void)
{
	fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);		
}
int main(void)
{
	f();
	printf("hello world\n");
	return 0;
}
