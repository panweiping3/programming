#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
        char *initrd = "13wewqqeeqd-2.6.7.img";
        char *ch = strchr(initrd, '-');
        char name[64];
        memset(name, '\0', 64);
        strncpy(name, initrd, ch - initrd);
        printf("%s\n", initrd);
        printf("%s\n", name);

        return 0;
}
