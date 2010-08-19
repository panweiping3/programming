#include<stdio.h> 
typedef struct { 
  char i; 
  int j; 
  char k; 
}Test; 

#define container_of(ptr, type, member) ({          		\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

int main() 
{ 
  	Test *p = 0; 
	printf("&p->j=%x, offest(j)=%d\n",  &(p->j), __builtin_offsetof(Test, j)); 

	Test t;
	t.i = 1;
	t.j = 2;
	t.k = 3;

	printf("struct Test i=%d, j=%d, k=%d\n", t.i, t.j, t.k);

	char *pp = &t.k;
	p = container_of(pp, Test, k);
	printf("struct Test i=%d, j=%d, k=%d\n", p->i, p->j, p->k);

	return 0;
} 
