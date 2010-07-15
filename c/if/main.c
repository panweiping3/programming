/*
 * 在if语句中， i-=是执行的，i的值是改变的
 */

#include <stdio.h>
#include <sys/time.h>

int main()
{
	int i = 100;
	
	fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);	
	printf("i=%d\n", i);
	if ((i -= 10) > 100) {
		fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);	
		printf("i=%d\n", i);
	} else if ((i -= 10) > 99) {
		fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);	
		printf("i=%d\n", i);
	} else if ((i -= 10) > 98) {
		fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);	
		printf("i=%d\n", i);
	} 
	
	fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);	
	printf("i=%d\n", i);
	return 0;
}
