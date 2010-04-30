#include <QMap>

#include "libsb.h"
#include "sb_http.h"

QMap <int, SBHttp *> net_g;

int open_network(const char *url, int port, NETWORK_TYPE type)
{
    if (type == HTTP) {
        SBHttp *http = new SBHttp();
        http->setUrl(QUrl(url));
        http->setPort(port);
        int fd = net_g.size();
        net_g.insert(fd, http);
        return fd;
    }

    return -1;
}

int send_start(int fd, const char *filename)
{
    if (net_g.value(fd)) {
        net_g.value(fd)->post_start(net_g.value(fd)->getUrl(), filename);
        return 0;
    }

    return -1;
}

int send_end(int fd)
{
    if (net_g.value(fd)) {
        net_g.value(fd)->post_end();
        return 0;
    }

    return -1;
}

int send_data(int fd, const char *buf, long long size)
{
    if (net_g.value(fd)) {
        net_g.value(fd)->post_data(buf, size);
        return 0;
    }

    return -1;
}
    
int close_network(int fd)
{
    if (net_g.value(fd)) {
        net_g.remove(fd);
        return 0;
    }

    return -1;
}
