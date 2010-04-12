#include <stdio.h>

#define PWP 10

int main(int argc, char *argv[])
{
	if (__builtin_constant_p(PWP))
	{
		fprintf(stdout, "constant\n");
	}
	else
	{
		fprintf(stdout, "variable\n");
	}

	return 0;
}
