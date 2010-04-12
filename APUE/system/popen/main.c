#include "popen.h"

int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    int status;

    if ((fp = popen("sleep 20", "r")) == NULL) {
        fprintf(stderr, "popen error\n");
        exit(1);
    }

    fprintf(stderr, "popen returnned, but\n");
    fprintf(stderr, "the child is sleeping\n");
    
    status = pclose(fp);

    if (WIFEXITED(status)) {
        fprintf(stderr, "the child is finishing\n");
        return 0;
    }
}
