#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define MAX_SECTION_LEN 0x1000

static int MultiCastRecv(int port, char * multi_ip)
{
	int socket_fd = -1;
	struct sockaddr_in local_addr,source_addr;
	struct ip_mreq mreq;
	int flags, packet_len = 0, source_addr_len;
	fd_set  rset;
	struct timeval timeout;
	static char buffer[MAX_SECTION_LEN];

	socket_fd = socket(AF_INET,SOCK_DGRAM,0);
	if (socket_fd < 0) {
		perror("open socket error!\n");	
		return -1;
	}
	fprintf(stderr, "Create client socket successfully.\n");

	memset(&local_addr,0,sizeof(local_addr));
	local_addr.sin_family = AF_INET; 
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	local_addr.sin_port = htons(port); 

	if (bind(socket_fd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0) {
		perror("bind broadcast address error.");
		return -1;
	}
	fprintf(stderr, "Socket bind successfully.\n");

	if (multi_ip) {
		inet_aton(multi_ip, &mreq.imr_multiaddr);
		mreq.imr_interface.s_addr = htonl(INADDR_ANY);
		if (setsockopt(socket_fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq))< 0) {
			perror("setsockopt error.");
			//return -1;
		}
		fprintf(stderr, "Add group successfully.\n");
	}

	flags = fcntl(socket_fd, F_GETFL, 0);
	fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);

	fprintf(stderr, "Start while loop for receiving data.\n");

	while(1) {
		while(1) {
			timeout.tv_sec=0;
			timeout.tv_usec=10000;
			FD_ZERO(&rset); 	
			FD_SET(socket_fd, &rset);
			if (select(socket_fd+1, &rset, NULL, NULL, &timeout) < 0) {
				if (errno == EINTR) {
					continue;
				} else {
					perror("select");
					return -1;
				}
			}	
			break;
		}

		if (FD_ISSET(socket_fd, &rset)) {
			source_addr_len = sizeof(source_addr);
			memset(buffer, '\0', MAX_SECTION_LEN);
			packet_len = recvfrom(socket_fd,
						buffer,
						MAX_SECTION_LEN,
						0,
						(struct sockaddr *)&source_addr, 
						&source_addr_len);
			if (packet_len < 0) {
				if( (errno != EAGAIN) && (errno != EWOULDBLOCK) ) {
					perror("recvfrom");
					return -1;
				}
			} else if (packet_len > 0) {
				fprintf(stderr, "src ip=%s,src_port=%d\n",
					inet_ntoa(source_addr.sin_addr),
					ntohs(source_addr.sin_port));
				fprintf(stderr, "\n");
				fwrite(buffer, packet_len, 1, stdout);
				fflush(stdout);
			}
		}
	}
}


int main(int argc, char * argv[])
{
	if (argc == 3) {
		MultiCastRecv(atoi(argv[1]), argv[2]);
	} else if (argc == 2) {
		MultiCastRecv(atoi(argv[1]), NULL);
	} else {
		fprintf(stderr, "usage:%s port [multi_ip]\n", argv[0]);
	}
	return 0;	
}
