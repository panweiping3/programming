#include <stdio.h>

int k = 0;
int *kp = &k;

void *fff(void *i)
{
	return i ?: kp;
}

int main(void)
{	
	int m = 100;
	void *i = &m;
	void *j = NULL;
	
	printf( "hello world &k=0x%x\n", &k );
	printf( "hello world &m=0x%x\n", &m );
	printf( "hello world  i=0x%x\n", i );
	printf( "hello world  j=0x%x\n", j );


	printf( "hello world   =0x%x\n", fff(i));
	printf( "hello world   =0x%x\n", fff(j));
	return 0;
}
