#include <stdio.h>
#include <sys/time.h>

int main()
{
	int i = 0x12345678;
	char *p0 = (char *)&i;
	char *p1 = (char *)&i + 1;
	char *p2 = (char *)&i + 2;
	char *p3 = (char *)&i + 3;

	printf("&i=%x\n", &i);
	printf("p0=%x *p%d=%x\n",  p0, 0,*p0);	
	printf("p0=%x *p%d=%x\n",  p1, 1,*p1);	
	printf("p0=%x *p%d=%x\n",  p2, 2,*p2);	
	printf("p0=%x *p%d=%x\n",  p3, 3,*p3);	
	return 0;
}
