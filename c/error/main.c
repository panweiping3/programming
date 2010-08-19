#include <stdio.h>

#define ENOMEM      12  /* Out of memory */
#define EACCES      13  /* Permission denied */
#define EFAULT      14  /* Bad */

static inline void *ERR_PTR(long error)
{
    return (void *) error;
}

static inline long PTR_ERR(const void *ptr)
{
    return (long) ptr;
}   

static inline long IS_ERR(const void *ptr)
{   
    return (unsigned long)ptr > (unsigned long)-1000L;
}   

int main()
{
	char *p = ERR_PTR(-ENOMEM);	

	if (IS_ERR(p)) {
		fprintf(stderr, "error\n");	
	} else {
		fprintf(stderr, "ok\n");	
	}

	char *q = ERR_PTR(-1000);	

	if (IS_ERR(q)) {
		fprintf(stderr, "error\n");	
	} else {
		fprintf(stderr, "ok\n");	
	}

	unsigned long r = (-1000);
	unsigned long s = (-ENOMEM);

	fprintf(stderr, "-1000=0x%x\n", r);	
	fprintf(stderr, "-12  =0x%x\n", s);	
	return 0;
}
