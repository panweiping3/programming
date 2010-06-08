#include <stdio.h>
#include <stdlib.h>

typedef long long INT64;
typedef unsigned long long INT64U;
typedef int INT32;
typedef unsigned int INT32U;

int main(int argc, char* argv[])
{
	INT32 it1 = 2147483647; //2^31-1
	INT64 it2 = 9223372036854775807LL; //2^63-1
	INT32U it3= 4294967295UL; //2^32-1
	INT64U it4= 18446744073709551615ULL; //2^64-1
	printf("it1=%d,it2=%d,it3=%d,it4=%d\n",sizeof(it1),sizeof(it2),sizeof(it3),sizeof(it4));
	printf("it1=%d,it2=%lld,it3=%u,it4=%llu \n",it1,it2,it3,it4);
	printf("it1=%d,it2=%lld,it3=%u,it4=%llu \n",it1 + 1, it2 + 1, it3 + 1, it4 + 1);

	return 0;
}
