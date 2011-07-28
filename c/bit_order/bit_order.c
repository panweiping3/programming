#include <stdio.h>  

//#define BYTE unsigned char
#define BYTE char
typedef struct
{
	BYTE a:1;
	BYTE b:1;
	BYTE c:1;
	BYTE d:1;
	BYTE e:1;
	BYTE f:1;
	BYTE g:1;
	BYTE h:1;
}TestBit;


int main(int argc, char* argv[])
{
	char c = 0x96; /* 10010110 */
	TestBit *q = NULL;
	
	q = (TestBit *)&c;
	printf("q->a = %d\n", q->a);
	printf("q->b = %d\n", q->b);
	printf("q->c = %d\n", q->c);
	printf("q->d = %d\n", q->d);
	printf("q->e = %d\n", q->e);
	printf("q->f = %d\n", q->f);
	printf("q->g = %d\n", q->g);
	printf("q->h = %d\n", q->h);

	TestBit d = 
	{.a=1,
	.b=1}; /* 10010110 */
	printf("d.a = %d\n", d.a);
    return 0;
}
