#include <stdio.h>
#include <sys/time.h>

#define ENDIANNESS(x) ((char)x.l)

int main()
{
	int i = 0x12345678;
	char *p0 = (char *)&i;
	char *p1 = (char *)&i + 1;
	char *p2 = (char *)&i + 2;
	char *p3 = (char *)&i + 3;

	printf("i=%x\n", i);
	printf("&i=%x\n", &i);
	printf("p0=%x *p%d=%x\n",  p0, 0,*p0);	
	printf("p0=%x *p%d=%x\n",  p1, 1,*p1);	
	printf("p0=%x *p%d=%x\n",  p2, 2,*p2);	
	printf("p0=%x *p%d=%x\n",  p3, 3,*p3);	
	
	short j = 0x1234;
	char *pp0 = (char *)&j;
	char *pp1 = (char *)&j + 1;
	char *pp2 = (char *)&j + 2;
	char *pp3 = (char *)&j + 3;

	printf("j=%x\n", j);
	printf("&j=%x\n", &j);
	printf("pp0=%x *p%d=%x\n",  pp0, 0, *pp0);	
	printf("pp0=%x *p%d=%x\n",  pp1, 1, *pp1);	
	printf("pp0=%x *p%d=%x\n",  pp2, 2, *pp2);	
	printf("pp0=%x *p%d=%x\n",  pp3, 3, *pp3);	

	unsigned char jj = 0x12;
	unsigned char jj_0 = jj >> 4;
	unsigned char jj_1 = jj & 0x0f;

	printf("jj=%x\n", jj);
	printf("jj = %x\n", jj);	
	printf("jj_0 = %x\n", jj_0);	
	printf("jj_1 = %x\n", jj_1);	

	union endian_test{ 
		char c[4]; 
		unsigned long l; 
	};
	
	union endian_test t = { { 'l', '?', '?', 'b' } };

	for (i=0;i<4;++i) {
		printf("&t.c[%d]=%x, t.c[%d]=%c\n", i, &t.c[i], i, t.c[i]);
	}

	if (ENDIANNESS(t) == 'l') {
		printf("little endian\n");
	} else {
		printf("big endian\n");
	}


	struct iphdr {
	unsigned char ihl:4, version:4;
	};

	struct iphdr l;
	l.ihl = 7;
	l.version = 3;

	printf("&l.ihl=%x\n", l.ihl);
	printf("&l.version=%x\n", l.version);
	printf("&l=%x\n", &l);
	printf("sizeof(struct iphdr)=%d\n", sizeof(struct iphdr));
	printf("l=%d\n", l);

	unsigned short kk = (4 << 12) | (5 << 8);
	printf("kk=%x\n", kk);

	return 0;
}
