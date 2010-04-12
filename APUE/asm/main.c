#include <stdio.h>
static inline int _strncmp(const char * cs,const char * ct,size_t count)
{
        register int __res;
        int d0, d1, d2;
        __asm__ __volatile__(
                        "1:\tdecl %3\n\t"
                        "js 2f\n\t"
                        "lodsb\n\t"
                        "scasb\n\t"
                        "jne 3f\n\t"
                        "testb %%al,%%al\n\t"
                        "jne 1b\n"
                        "2:\txorl %%eax,%%eax\n\t"
                        "jmp 4f\n"
                        "3:\tsbbl %%eax,%%eax\n\t"
                        "orb $1,%%al\n"
                        "4:"
                        :"=a" (__res), "=&S" (d0), "=&D" (d1), "=&c" (d2)
                        :"1" (cs),"2" (ct),"3" (count));
        printf("__res %d\n", __res);
        return __res;
}


int main(int argc, char *argv[])
{
    char *p1 = "1244";
    char *p2 = "124884";

    return _strncmp(p1, p2, 5);
}
