#include <stdio.h>

#define dbg_debugfs_exit_fs(c)                     0

int main()
{
    #ifdef DEBUG
	    printf("DEBUG DEFINED\n");
	    printf("DEBUG UNDEFINED\n");
    #endif
    
    const char *c="sssssss";
    dbg_debugfs_exit_fs(c);

    0;
    return 0;
}
