#include <stdio.h>

char buf[2] = {1,1};

int main(int argc, char *argv[])
{
	int i;
	char a[2] = {2,2};

	for (i=0; i<2; ++i) {
		fprintf(stdout, "buf[%d]=%d\n", i, buf[i]);
	}

	buf = a;
	for (i=0; i<2; ++i) {
		fprintf(stdout, "buf[%d]=%d\n", i, buf[i]);
	}

	return 0;	
}
