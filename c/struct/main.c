#include <stdio.h>
    
struct s{
	unsigned short flag;
	unsigned short meta_flag;
	unsigned int offset;
	char UUID[40];
	char HOST[40];
};

int main(int argc, char *argv[])
{
    struct s s_t;


    printf("%d\n", sizeof(struct s));
    printf("%x\n", &s_t.flag);
    printf("%x\n", &s_t.meta_flag);
    printf("%x\n", &s_t.offset);
    printf("%x\n", &s_t.UUID);
    printf("%x\n", &s_t.HOST);
    return 0;
}
