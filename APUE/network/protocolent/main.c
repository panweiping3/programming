/*
 * This program is to read file /etc/protocols
 * TODO:
 * What's the use of /etc/protocols ?
 */

#include <stdio.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    struct protoent *protoent_p = NULL;

    setprotoent(0);
    while ((protoent_p = getprotoent()) != NULL) {
        printf("%-20s\t", protoent_p->p_name);
        printf("%d\t\n", protoent_p->p_proto);
    }
    endprotoent();

    return 0;
}
