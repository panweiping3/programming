#include <stdio.h>
#include <stdlib.h>

#define GET_ESP(esp) do { \
    asm volatile ("movl %%esp, %0\n\t" : "=m" (esp)); \
} while (0)


#define K 1024

int main() {
    char* c;
    int i = 0;
    unsigned long esp;

    GET_ESP (esp);
    printf ("Current stack pointer is %#x\n", esp);

    while (1) {
        c = (char*)esp - i * K;
        *c = 'a';
        GET_ESP (esp);
        printf ("esp = %#x, overflow %dK\n", esp, i);
        i++;
    }
}
