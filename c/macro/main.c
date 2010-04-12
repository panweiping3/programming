#include <stdio.h>

int main(int argc, char *argv[])
{
#ifdef PWP
    if (PWP == 1) {
        printf("defined PWP\n");
    }
#else
    printf("undefined PWP\n");
#endif
}
