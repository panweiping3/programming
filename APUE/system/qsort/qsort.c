#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int compare(const void *p1, const void *p2)
{
    return ((*((int *)p1)) - (*((int *)p2)));
}

int main()
{
    int i;
    int m[10] = {1,5,-1,4,7,-3,56,3,1,0};

    printf("before sortin\n");
    for (i = 0; i < SIZE; ++i) {
        printf("m[%d]:%d\n", i, m[i]);
    }

    qsort(m, SIZE, sizeof(int), compare);  

    printf("after sortin\n");
    for (i = 0; i < SIZE; ++i) {
        printf("m[%d]:%d\n", i, m[i]);
    }
}

