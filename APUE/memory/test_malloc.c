#include <stdio.h>
#include <stdlib.h>

#define G 1024*1024*1024
#define M 1024*1024
#define K 1024

int main(int argc, char *argv[])
{
    int i;
    if (argc != 2) {
        fprintf(stderr, "you shoule use ./a 1 MB\n");
        exit(1);
    }
    
    int size = atoi(argv[1]);

    for (i= 1; i <= size * K; ++i) {
        char *p = malloc(K);
        if (p != NULL) {
            fprintf(stderr, "I've malloc %d KB memory\n", i);
            *p = 120;
        } else {
            fprintf(stderr, "malloc memory error\n");
            exit(1);
        }
    }

    if (i == size * K + 1) {
        fprintf(stderr, "malloc finishing! waiting\n");
        pause();
    }
}
