#include <stdio.h>
#include <stdlib.h>

void func( char str[100])
{
    fprintf(stderr, "%s %d %s :sizeof(str)=%d\n", __FILE__, __LINE__, __func__, sizeof(str));
}

int main()
{
	char a[] = "hello";
    fprintf(stderr, "%s %d %s :sizeof(a)=%d\n", __FILE__, __LINE__, __func__, sizeof(a));
	char *p  = a;
    fprintf(stderr, "%s %d %s :sizeof(p)=%d\n", __FILE__, __LINE__, __func__, sizeof(p));
	void *pStr = malloc(100);
    fprintf(stderr, "%s %d %s :sizeof(pStr)=%d\n", __FILE__, __LINE__, __func__, sizeof(pStr));

    func(a);

    return 0;
}
