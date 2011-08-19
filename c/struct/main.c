#include <stdio.h>
    
struct s{
	unsigned short flag;
	unsigned short meta_flag;
	void *offset;
	char UUID[40];
	char HOST[40];
	void pp (void)
	{
		fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);		
	}
};

void p(struct s *s_t)
{

	int *o = s_t->offset;

    printf("%x\n", (unsigned int)o);
}

int main(int argc, char *argv[])
{
    struct s s_t;
	
	p(&s_t);

	s_t.pp();

    return 0;
}
