#include <stdio.h>
int main(void)
{
	int a,b,c;

	a=1;
	b=10;
	c=0;
	return (a || (b ? c:0));
}
