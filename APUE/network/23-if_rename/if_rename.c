#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <net/if.h>
#include <netinet/ether.h>

int main(int argc,char **argv)
{
	int s;
	struct ifreq ifr;

	if (argc != 3)
	{
		fprintf(stderr,"Usage: %s old_name new_name\n",argv[0]);
		exit(-1);
	}

	s = socket(PF_INET, SOCK_DGRAM, 0);
	strncpy(ifr.ifr_name,argv[1],IFNAMSIZ);
	strncpy(ifr.ifr_newname,argv[2],IFNAMSIZ);
	if (ioctl(s, SIOCSIFNAME, &ifr) < 0) {
		perror("SIOCSIFNAME");
	}

	close(s);
	return 0;
}
