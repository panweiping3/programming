#include <stdio.h>

struct qstr {
	unsigned int hash;
	unsigned int len;
	const unsigned char *name;
};

int main(int argc, char *argv[])
{
	const char *p = "abc";	
	p[0] = 'd';
	return 0;
}
