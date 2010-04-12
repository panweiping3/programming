#include <stdio.h>

int data[32];

int main()
{
    int i;

    for (i=0; i<32; ++i) {
        printf("data[%d]=%d\n",i, data[i]);
    }

    printf("ptrace data addr 0x%x\n", data);

    return 0;
}
