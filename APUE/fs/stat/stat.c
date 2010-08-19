#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "you should use  ./stat file\n");
        exit(1);
    }
    
    struct stat buf;
	errno = 0;
    if (stat(argv[1], &buf)) {
        perror("stat error:");
    }

    fprintf(stderr, "st_size:%d\n", buf.st_size);

	errno = 0;
    if (lstat(argv[1], &buf)) {
        perror("lstat error:");
    }

    fprintf(stderr, "st_size:%d\n", buf.st_size);

	errno = 0;
    if (stat64(argv[1], &buf)) {
        perror("stat64 error:");
    }

    fprintf(stderr, "st_size:%lld\n", buf.st_size);

	errno = 0;
    if (lstat64(argv[1], &buf)) {
        perror("lstat64 error:");
    }

    fprintf(stderr, "st_size:%lld\n", buf.st_size);
    return 0;
};


