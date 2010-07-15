#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 1024

int main()
{
	FILE *fp = fopen("./sda2_sb", "r");
	if (!fp) {
		fprintf(stderr, "%s %d %s fopen error\n", __FILE__, __LINE__, __func__);
		return -1;
	}

	fseek(fp, 56, SEEK_SET);
	short data;
	if (fread((void *)&data, 1, sizeof(short), fp) != sizeof(short)) {
		fprintf(stderr, "%s %d %s fread error\n", __FILE__, __LINE__, __func__);	
		return -2;
	}
	
	fprintf(stdout, "data=%x\n", data);

	return 0;
}
