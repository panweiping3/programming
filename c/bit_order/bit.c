#include <stdio.h>

struct zz {
	unsigned char a:1;
	unsigned char b:1;
	unsigned char c:1;
	unsigned char d:1;
	unsigned char e:1;
	unsigned char f:1;
	unsigned char j:1;
	unsigned char h:1;
};

struct {
	union {
		unsigned char x;
		struct zz z;
	} u;
} u;

int main(int argc, char ** argv)
{
	int i;
	u.u.x = 0x45;

	printf("sizeof(struct zz)=%d\n", sizeof(struct zz));
	printf("sizeof(u)=%d\n", sizeof(u));

	printf("u.u.x=%x\n", u.u.x);
	printf("u.u.x=%d\n", u.u.x);
	printf("u.u.a=%d\n", u.u.z.a);
	printf("u.u.b=%d\n", u.u.z.b);
	printf("u.u.c=%d\n", u.u.z.c);
	printf("u.u.d=%d\n", u.u.z.d);
	printf("u.u.e=%d\n", u.u.z.e);
	printf("u.u.f=%d\n", u.u.z.f);
	printf("u.u.j=%d\n", u.u.z.j);
	printf("u.u.h=%d\n", u.u.z.h);

	return 0;
}
