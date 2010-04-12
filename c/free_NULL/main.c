#include <stdio.h>
#include <stdlib.h>

int main()
{
    free(NULL);
    printf("free NULL is OK\n");
    return 0;
}

