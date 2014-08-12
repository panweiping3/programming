#include "header.h"

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in toAddr;
	struct sockaddr_in fromAddr;
	char *data;
	int i;
    	unsigned long target_speed = 1024*1024;

	if (argc != 2) {
		printf("./client IPaddres\n");
		exit(1);
	}

	sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (sock < 0) {
		printf(" create socket error \n");
		exit(1);
	}

	// restrict the speed to 1048576 B/s
	#ifdef SO_MAX_PACING_RATE 
        if (setsockopt(sock, SOL_SOCKET, SO_MAX_PACING_RATE,
			&target_speed, sizeof(target_speed)))
		printf("SO_MAX_PACING_RATE error\n");
	else
		printf("SO_MAX_PACING_RATE ok\n");
	#endif

	memset(&toAddr,0,sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_addr.s_addr = inet_addr(argv[1]);
	toAddr.sin_port = htons(4000);

	data = malloc(DATA_SIZE);
	memset(data, 'a', DATA_SIZE);
	
	while (1) {
		if (sendto(sock, data, DATA_SIZE+1, 0, 
			(struct sockaddr*)&toAddr, sizeof(toAddr)) == -1) {
			printf("sendto() error\n");
			close(sock);
			exit(1);
		}
	}

	close(sock);

	return 0;
}

