#include <stdio.h>

struct ccc{
	int t;
};

struct abc{
	int a;
	int b;
	int c;
	struct ccc dd;
};


int main(int argc, char * argv[])
{
	struct abc xx,yy;
	xx.a=1;
	xx.b=2;
	xx.c=3;
	xx.dd.t=4;

	yy = xx;

	if (yy.a == xx.a) {
		fprintf(stderr, "%s %d %s yy==xx\n", __FILE__, __LINE__, __func__);
	} else {
		fprintf(stderr, "%s %d %s yy<>xx\n", __FILE__, __LINE__, __func__);	
	}
	return 0;
}
