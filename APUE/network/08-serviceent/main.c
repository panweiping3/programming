/*
 * This program is to read file /etc/services
 * TODO:
 * What's the use of /etc/services ?
 * You can lookup this file. But if you want to change the port of a service,
 * goto THE service config file.
 */

#include <stdio.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    struct servent *servent_p = NULL;

    setservent(0);
    while ((servent_p = getservent()) != NULL) {
        printf("%-20s\t", servent_p->s_name);
        printf("%10d\t", servent_p->s_port);
        printf("%-20s\n", servent_p->s_proto);
    }
    endservent();

    return 0;
}
