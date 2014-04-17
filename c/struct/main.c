#include <stdio.h>
    
struct s{
	unsigned short flag;
	unsigned short meta_flag;
	void *offset;
	char UUID[40];
	char HOST[40];
};

void p(struct s *s_t)
{

	int *o = s_t->offset;

    printf("%x\n", (unsigned int)o);
}

int main(int argc, char *argv[])
{
    struct s s_t;
    struct s *s_t_p = &s_t;

    printf("sizeof=%d\n", sizeof(s_t_p));
	
	p(&s_t);

//	s_t.pp();

    return 0;
}
