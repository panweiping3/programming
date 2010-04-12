#include <stdio.h>
#include <stdlib.h>

int main()
{
	char content[] = "pwp: hello world";
	int size = sizeof(content);

	FILE *fp = NULL;

	if ((fp = fopen("./data", "w+")) == NULL)
	{
		perror("create data error");
	
		exit(1);
	}

	if ((fwrite(content, sizeof(char), size, fp)) != size)
	{
		perror("fwrite error");

		exit(2);
	}	

	fclose(fp);

	getchar();

	if ((truncate("./data", size+10)) != 0)
	{
		perror("ftruncate error");

		exit(3);
	}	

}
