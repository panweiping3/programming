#include <unistd.h>
#include <stdio.h>
#define BRKSIZE	4096
#define MAX	(1024*1024)

int main ()
{
	long i=0, *p, ret;
	void *addr;

	addr=sbrk(0);
	for (i=1; i<MAX; i++) {
		addr += BRKSIZE;
		ret=brk(addr);
	        if (ret == -1)
 			break;
	        /* 
		 * Need below codes? have a try, 
		 * Which will reclaim memory surprise
                 */
		/*
		if (i > 100 * 1024)
			break;
		p=(long *)(addr-BRKSIZE); 
		*p=1234;
		*/
	}
	printf("Get %luM memory, it's overcommit memry?\n", i*4/BRKSIZE);
	getchar();
	return 0;
}
