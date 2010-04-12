#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char envbuf[128];
extern char **environ;

char *getenv(const char *name)
{
    int i;
    int len = strlen(name);

    for (i = 0; environ[i] != NULL; ++i) {
        if (strncmp(environ[i], name, len) == 0) {
            strncpy(envbuf, strchr(environ[i], '=') + 1, 128);
            return envbuf;
        }
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "./a.out aa\n");
        return 1;
    }

    fprintf(stdout, "%s=%s\n", argv[1], getenv(argv[1]));

    return 0;
}
