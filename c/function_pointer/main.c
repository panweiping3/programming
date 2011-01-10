#include <stdio.h>

int a(double d)
{
    fprintf(stderr, "%s %d %s :a\n", __FILE__, __LINE__, __func__);   
    return 0;
}

int b(double d)
{
    fprintf(stderr, "%s %d %s :b\n", __FILE__, __LINE__, __func__);   
    return 0;
}

int c(double d)
{
    fprintf(stderr, "%s %d %s :c\n", __FILE__, __LINE__, __func__);   
    return 0;
}

int d(double d)
{
    fprintf(stderr, "%s %d %s :d\n", __FILE__, __LINE__, __func__);   
    return 0;
}

int e(double d)
{
    fprintf(stderr, "%s %d %s :e\n", __FILE__, __LINE__, __func__);   
    return 0;
}

int main()
{
    int i;
    
    int (*FuncArray[5])(double d);

    FuncArray[0] = &a;
    FuncArray[1] = &b;
    FuncArray[2] = &c;
    FuncArray[3] = &d;
    FuncArray[4] = &e;

    for (i=0; i<5; ++i) {
        FuncArray[i](i);
    }

    int (*p)(double d);
    p = e;
    p(6);

    fprintf(stderr, "%s %d %s a=%x\n", __FILE__, __LINE__, __func__, a);   
    fprintf(stderr, "%s %d %s &a=%x\n", __FILE__, __LINE__, __func__, &a);   
    fprintf(stderr, "%s %d %s *a=%x\n", __FILE__, __LINE__, __func__, *a);   



    return 0;
}
