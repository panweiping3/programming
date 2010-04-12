#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *p = (char *)malloc(10);
    free(p);
    free(p);
    return 0;
}
