#include "processpool.h"
#include "cgi_conn.h"

int cgi_conn::m_epollfd = -1;

int main(int argc, char *argv[])
{
	if (argc <= 2) {
		printf("usage : %s ip_address port_number\n", basename(argv[0]));
		return 1;
	}

	const char *ip = argv[1];
	int port = atoi(argv[2]);

	int listenfd = socket(PF_INET, SOCK_STREAM, 0);
	assert(listenfd >= 0);

	int ret = 0;
	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);

	ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
	assert(ret != -1);

	ret = listen(listenfd, 5);
	assert(ret != -1);

	processpool<class cgi_conn>* pool = processpool<class cgi_conn>::create(listenfd);
	if (pool) {
		pool->run();
		delete pool;
	}

	close(listenfd);

	return 0;
}
