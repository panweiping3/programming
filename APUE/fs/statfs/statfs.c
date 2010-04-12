#include <stdio.h>
#include <stdlib.h>
#include <sys/vfs.h>    /* or <sys/statfs.h> */

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "you should use  ./statsfs  mountpoint\n");
        exit(1);
    }
    
    struct statfs buf;

    if (statfs(argv[1], &buf)) {
        fprintf(stderr, "statfs error\n");
        exit(1);
    }

    fprintf(stderr, "f_type   :%ld\n", buf.f_type);
    fprintf(stderr, "f_bsize  :%ld\n", buf.f_bsize);
    fprintf(stderr, "f_blocks :%ld\n", buf.f_blocks);
    fprintf(stderr, "f_bfree  :%ld\n", buf.f_bfree);
    fprintf(stderr, "f_bavail :%ld\n", buf.f_bavail);
    fprintf(stderr, "f_files  :%ld\n", buf.f_files);
    fprintf(stderr, "f_ffree  :%ld\n", buf.f_ffree);
    fprintf(stderr, "f_namelen:%ld\n", buf.f_namelen);

    return 0;
};


