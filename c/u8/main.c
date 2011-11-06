#include <stdio.h>

/*
    bonding: comparing a u8 with -1 is always false
        
	    slave->duplex is a u8 type so the in bond_info_show_slave() when we
	        check "if (slave->duplex == -1)", it's always false.
*/
#define SPEED_UNKNOWN          -1

int main(void)
{
{
	char p = SPEED_UNKNOWN;
	printf("char p sizeof(p) = %d\n", sizeof(p));
	if (p == SPEED_UNKNOWN )
		printf("p == SPEED_UNKNOWN\n");
	else
		printf("p != SPEED_UNKNOWN\n");
}

{
	unsigned char p = SPEED_UNKNOWN;
	printf("unsigned char p sizeof(p) = %d\n", sizeof(p));
	if (p == SPEED_UNKNOWN )
		printf("p == SPEED_UNKNOWN\n");
	else
		printf("p != SPEED_UNKNOWN\n");
}

	printf("\n\n");

{
	short p = SPEED_UNKNOWN;
	printf("short p sizeof(p) = %d\n", sizeof(p));
	if (p == SPEED_UNKNOWN )
		printf("p == SPEED_UNKNOWN\n");
	else
		printf("p != SPEED_UNKNOWN\n");
}

{
	unsigned short p = SPEED_UNKNOWN;
	printf("unsigned short p sizeof(p) = %d\n", sizeof(p));
	if (p == SPEED_UNKNOWN )
		printf("p == SPEED_UNKNOWN\n");
	else
		printf("p != SPEED_UNKNOWN\n");
}

	printf("\n\n");
{
	int p = SPEED_UNKNOWN;
	printf("int p sizeof(p) = %d\n", sizeof(p));
	if (p == SPEED_UNKNOWN )
		printf("p == SPEED_UNKNOWN\n");
	else
		printf("p != SPEED_UNKNOWN\n");
}

{
	unsigned int p = SPEED_UNKNOWN;
	printf("unsigned int p sizeof(p) = %d\n", sizeof(p));
	if (p == SPEED_UNKNOWN )
		printf("p == SPEED_UNKNOWN\n");
	else
		printf("p != SPEED_UNKNOWN\n");
}

	printf("\n\n");
{
	long p = SPEED_UNKNOWN;
	printf("long p sizeof(p) = %d\n", sizeof(p));
	if (p == SPEED_UNKNOWN )
		printf("p == SPEED_UNKNOWN\n");
	else
		printf("p != SPEED_UNKNOWN\n");
}

{
	unsigned long p = SPEED_UNKNOWN;
	printf("unsigned long psizeof(p) = %d\n", sizeof(p));
	if (p == SPEED_UNKNOWN )
		printf("p == SPEED_UNKNOWN\n");
	else
		printf("p != SPEED_UNKNOWN\n");
}
	printf("\n\n");

	printf("sizeof(-1)=%d\n", sizeof(-1));
	printf("%d\n", -1);
	printf("%u\n", -1);

	unsigned int right = 1;
	char left = -1;

	if(left < right)printf("%d < %d\n", left, right);
	else if(left == right)printf("%d = %d\n", left, right);
	else printf("%d > %d\n", left, right);

	return 0;
}
