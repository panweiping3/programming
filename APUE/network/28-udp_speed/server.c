#include "header.h"

int main(int argc, char *argv[])
{
	struct sockaddr_in fromAddr; 	//在recvfrom中使用的对方主机地址
	int sock;
	struct sockaddr_in toAddr; 	//sendto中使用的对方地址
	int recvLen;
	unsigned long long total_len = 0;
	unsigned int addrLen;
	char *recvBuffer;
	struct timeval t_start, t_end;    //用于记录文件传输时间
	unsigned long long old_timeuse = 0;

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sock < 0) {
		printf(" create socket error\n");
		exit(0);
	}

	memset(&fromAddr, 0, sizeof(fromAddr));
	fromAddr.sin_family = AF_INET;
	fromAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	fromAddr.sin_port = htons(4000);
	if (bind(sock, (struct sockaddr*)&fromAddr, sizeof(fromAddr)) < 0) {
		printf("bind() error \n");
		close(sock);
		exit(1);
	}
	
	recvBuffer = malloc(DATA_SIZE);
	addrLen = sizeof(toAddr) + 16;
	gettimeofday(&t_start,NULL);
	while (1) {
		unsigned long long timeuse = 0;
		if((recvLen = recvfrom(sock, recvBuffer, DATA_SIZE, 0,
			(struct sockaddr*)&toAddr, &addrLen)) < 0) {
			printf("recvfrom() error\n");
			close(sock);
			exit(1); 
		}
		total_len += recvLen;

		gettimeofday(&t_end,NULL);
		timeuse = t_end.tv_sec - t_start.tv_sec;
		if ((timeuse != old_timeuse) && ((timeuse % 10) == 0)) {
			// print speed info every 10s
			unsigned long long speed = 0;
			speed = total_len/timeuse;
			printf("server:time:%llu speed:%llu B/s == %llu MB/s\n", timeuse, speed, speed >>20);
			old_timeuse = timeuse;
		}
	}
	
	close(sock);
	return 0;
}
