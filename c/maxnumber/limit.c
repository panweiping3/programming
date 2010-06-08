#include   <limits.h> 
#include   <stdio.h> 

int main()
{
	printf("CHAR_MIN=%d\n", CHAR_MIN);
	printf("CHAR_MAX=%d\n", CHAR_MAX);
	printf("SHRT_MIN=%d\n", SHRT_MIN);
	printf("SHRT_MAX=%d\n", SHRT_MAX);
	printf("INT_MIN=%d\n", INT_MIN);
	printf("INT_MAX=%d\n", INT_MAX);
	printf("UINT_MAX=%u\n", UINT_MAX);
	printf("LONG_MIN=%ld\n", LONG_MIN);
	printf("LONG_MAX=%ld\n", LONG_MAX);
	printf("ULONG_MAX=%lu\n", ULONG_MAX);
	printf("LLONG_MIN=%lld\n", LLONG_MIN);
	printf("LLONG_MAX=%lld\n", LLONG_MAX);
	printf("ULLONG_MAX=%llu\n", ULLONG_MAX);

	return 0;
}
