#include <stdio.h>

int main()
{
    int a, b;
    a= b = 10;
    typeof(a) c;
    c = b;
    printf("a=%d, b=%d, c=%d\n", a, b, c);
    return 0;
}
