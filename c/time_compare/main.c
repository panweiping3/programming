#include <stdio.h>

//#define time_after(unknown, known) ((long)known - (long)(unknown) < 0)
#define time_before(unknown, known) ((long)unknown - (long)(known) < 0)

unsigned int time_after(unsigned long t1, unsigned long t2)
{
    printf("-------------------t1=%-10u, t2=%-10u\n", t1, t2);
    printf("-------------------(long)t2=%-10u\n", (long)t2);
    printf("-------------------(long)t1 < 0=%-10u\n", (long)t1 < 0);
    return ((long)t2 - (long)(t1) < 0);
}

#define MAX 4294967295
int main()
{
    unsigned long t1, t2;
    t1 = MAX - 1;
    t2 = MAX;
    printf("t1=%-10u, t2=%-10u, time_after(t1, t2)=%u\n", t1, t2, time_after(t1,t2));

    t1 = MAX + 1;
    t2 = MAX - 1;
    printf("t1=%-10u, t2=%-10u, time_after(t1, t2)=%u\n", t1, t2, time_after(t1,t2));
    
    t1 = MAX + 1;
    t2 = MAX + 2;
    printf("t1=%-10u, t2=%-10u, time_after(t1, t2)=%u\n", t1, t2, time_after(t1,t2));
    
    return 0;
}
