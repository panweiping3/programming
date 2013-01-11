#include <stdio.h>
#include <string.h>


int main(void)
{
	char buf[3] = {'\0'};
	int m;
	int i = 1;

	memset(buf, 3, '\0');
	snprintf(buf, 2, "%02d", i);
	printf("i=%02d\n", i);
	printf( "hello world buf=%s\n", buf);
	for (m=0;m<3;m++)
		printf("buf[%d]=%c\n", m, buf[m]);

	memset(buf, 3, '\0');
	int j = 10;
	snprintf(buf, 2, "%02d", j);
	printf("j=%02d\n", j);
	printf( "hello world buf=%s\n", buf);
	for (m=0;m<3;m++)
		printf("buf[%d]=%c\n", m, buf[m]);

	memset(buf, 3, '\0');
	int k = 'x';
	snprintf(buf, 3, "%02d", k);
	printf("k=%02d\n", k);
	printf( "hello world buf=%s\n", buf);
	for (m=0;m<3;m++)
		printf("buf[%d]=%c\n", m, buf[m]);
	return 0;
}
