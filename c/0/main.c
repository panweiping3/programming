#include <stdio.h>

int main(int argc, char *argv[])
{
	char c = '\0';	
	if (c) {
		printf("c is not 0, c is true\n");
	} else {
		printf("c is 0, c is false\n");
	}

	char d = 0;	
	if (d) {
		printf("d is not 0, d is true\n");
	} else {
		printf("d is 0, d is false\n");
	}

	if (c == d) {
		printf("c==d\n");
	} else {
		printf("c<>d");
	}
	return 0;
}
