#include <stdio.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    struct netent *netent_p = NULL;

    setnetent(0);

    while ((netent_p = getnetent()) != NULL) {
        printf("netent_p->n_name: %s\n", netent_p->n_name);
        printf("netent_p->n_addrtype: %d\n", netent_p->n_addrtype);
        printf("netent_p->n_net: %d\n", netent_p->n_net);
        netent_p = NULL;
    }

    endnetent();

    return 0;
}
