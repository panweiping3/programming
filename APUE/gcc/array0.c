#include <stdio.h>
#include <stdlib.h>

struct pwp
{
	int a;
	int length;
	char aa[0];
};

int main(int argc, char *argv[])
{
	struct pwp *p = (struct pwp *)malloc(sizeof(struct pwp) + 4);
	p->a = 10;
	p->length = sizeof(struct pwp) + 4;
	(*p->aa) = 20;

	fprintf(stdout, "p address: %x \n", p);
	fprintf(stdout, "p->aa address: %x \n", &p->aa);
	fprintf(stdout, "p->a: %d \n", p->a);
	fprintf(stdout, "p->length: %d \n", p->length);
	fprintf(stdout, "p->aa: %d \n", *p->aa);
	
}
