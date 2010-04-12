#include <stdio.h>
#include <unistd.h>

int main()
{
    for (;;) {
        fprintf(stdout, "aaaaaaaaaaaaaaa\n");
        fprintf(stderr, "bbbbbbbbbbbbbbb\n");
        usleep(50000);
    }

    return 0;
}
