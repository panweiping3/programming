/*
 * use xor to exchange two numbers
 */

#include <stdio.h>

int main()
{
    int a, b, c;
    a = 99;
    b = 88;
    c = a ^ b;
    fprintf(stderr, "%s %d %s a=%d b=%d c=%d\n", __FILE__, __LINE__, __func__, a, b, c);
    fprintf(stderr, "%s %d %s a=%x b=%x c=%x\n", __FILE__, __LINE__, __func__, a, b, c);
    a = c ^ a;
    b = c ^ b;

    fprintf(stderr, "%s %d %s a=%d b=%d c=%d\n", __FILE__, __LINE__, __func__, a, b, c);
    fprintf(stderr, "%s %d %s a=%x b=%x c=%x\n", __FILE__, __LINE__, __func__, a, b, c);

    return 0;
}
