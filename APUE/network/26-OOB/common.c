#include "common.h" 

int Connect(char *addr)
{
	int fd;
	struct sockaddr_in server_addr;

	socklen_t socklen = sizeof(server_addr);

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		return -1;
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_aton(addr, &server_addr.sin_addr);
	server_addr.sin_port = htons(SERVER_PORT);

	if (connect(fd, (struct sockaddr*)&server_addr, socklen) < 0) {
		return -1;
	}

	return fd;
}

int BindAccept(char *addr)
{
	int fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	int length;

	socklen_t socklen = sizeof(server_addr);

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		return -1;
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_aton(addr, &server_addr.sin_addr);
	server_addr.sin_port = htons(SERVER_PORT);

	if (bind(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("bind to port %d failure!\n",SERVER_PORT);
		exit(1);
	}

	listen(fd, 5);

	while (1) {
		errno = 0;
		client_fd = accept(fd, (struct sockaddr*)&client_addr, &socklen);
		if (client_fd < 0) {
			perror("error comes when call accept!\n");
			break;
		} else	{
			return client_fd;
		}

	}

	return -1;
}

void bail(char *on_what)
{
	printf("%s\n");	
	exit(1);
}
