/*
 * This program is to read file /etc/networks
 * TODO:
 * What's the use of /etc/networks ?
 * Maybe it's related with route.
 */

#include <stdio.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    struct netent *netent_p = NULL;

    setnetent(0);
    while ((netent_p = getnetent()) != NULL) {
        printf("netent_p->n_name: %s\n", netent_p->n_name);
        printf("netent_p->n_addrtype: %d\n", netent_p->n_addrtype);
        printf("netent_p->n_net: %d\n\n", netent_p->n_net);
    }
    endnetent();

    return 0;
}
