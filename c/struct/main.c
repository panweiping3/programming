#include <stdio.h>
    
struct s{
    char i;
    int j;
};

int main(int argc, char *argv[])
{
    struct s s_t;

    printf("&s_t%llx\n", &s_t);
    printf("&s_t.i=%llx\n", &s_t.i);
    printf("&s_t.j=%llx\n", &s_t.j);

    return 0;
}
