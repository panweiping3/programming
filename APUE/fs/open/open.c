#include <stdio.h>

int main()
{
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	
	if ((fp1 = fopen("./read.c", "r+")) == NULL)
	{
		printf("open error");
		return -1;
	}

	if ((fp2 = fopen("./read.c", "r+")) == NULL)
	{
		printf("open error00000");
		return -1;
	}
}
