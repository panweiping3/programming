#include<string.h>
#include<stdio.h>

int main (int argc, char** argv)
{
    static const char foo[] = "abcdefg";
    printf("%s\n", foo);
    return 0;
} 
