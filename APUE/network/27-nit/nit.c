/* Tcp client program, It is a simple example only.

 * zhengsh 200520602061 2

 * connect to server, and echo a message from server.

 */

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv)
{  
	int client_fd;
	int i;
	struct sockaddr_ll      sll;

	memset(&sll, 0, sizeof(sll));
	sll.sll_family          = PF_PACKET;
	sll.sll_ifindex         = 0;
	sll.sll_protocol        = htons(ETH_P_ALL);
	sll.sll_pkttype		= htons(PACKET_HOST);

	if ((client_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
		fprintf(stderr, "create error!\n");
		exit(1);
	}

#if 0
	if (bind(client_fd, (struct sockaddr *) &sll, sizeof(sll))) {
		fprintf(stderr, "bind error!\n");
		exit(1);
	}
#endif
	fprintf(stderr, "%s %d %s \n", __FILE__, __LINE__, __func__);	
	while (1)
	{
		char buf[BUFFER_SIZE];
		int length;

		bzero(buf, BUFFER_SIZE);
		length = recv(client_fd, buf, BUFFER_SIZE, 0);
		if (length < 0) {
			fprintf(stderr, "error comes from server !");
			close(client_fd);
			exit(1);
		}

		fprintf(stderr, "from server: data start\n");
		for (i=0; i<length; ++i) {
			if ( i && i % 80 == 0)
				fprintf(stderr, "\n");

			fprintf(stderr, "%x ", buf[i]);
		}
		fprintf(stderr, "\nfrom server: data end\n");
	}

	close(client_fd);

	return 0;
}
