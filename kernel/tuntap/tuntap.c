#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>

unsigned short ChkSum(unsigned short *addr, int len) 
{ 
	register int nleft = len; 
	register unsigned short *w = addr; 
	register int sum = 0; 
	unsigned short answer = 0; 

	while (nleft > 1) {
		sum += *w++;
		nleft -= 2; 
	}

	if (nleft == 1) { 
		*(unsigned char *)(&answer) = *(unsigned char *)w; 
		sum += answer;
	} 
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return answer;
}

int tuntap_create (const char *dev)
{
	struct ifreq ifr;
	int fd;
	char *device = "/dev/net/tun";
	if ((fd = open (device, O_RDWR)) < 0)
		fprintf(stderr, "Cannot open TUN/TAP dev %s", device);

	memset (&ifr, 0, sizeof (ifr));
	ifr.ifr_flags = IFF_NO_PI;
	if (!strncmp (dev, "tun", 3)) {
		ifr.ifr_flags |= IFF_TUN;
	} else if (!strncmp (dev, "tap", 3)) {
		ifr.ifr_flags |= IFF_TAP;
	} else {
		fprintf(stderr, "I don't recognize device %s as a TUN or TAP device",dev);
	}

	if (strlen (dev) > 3)/* unit number specified? */
		strncpy (ifr.ifr_name, dev, IFNAMSIZ);

	if(ioctl(fd, TUNSETIFF, (void *)&ifr) < 0)
		fprintf(stderr, "Cannot ioctl TUNSETIFF %s", dev);

	if(ioctl(fd, TUNSETNOCSUM, (void *)&ifr) < 0)
		fprintf(stderr, "Cannot ioctl TUNSETNOCSUM %s", dev);

	fprintf(stderr, "TUN/TAP device %s opened\n", ifr.ifr_name);

	return fd;
}

int read_ip_data(char *file, char *data, int size)
{
	FILE *fp = NULL;
	int rsize;
	u_short checksum;
	
	fp = fopen(file, "rb");
	if (fp == NULL) {
		perror("fopen:");
		return 0;
	}
	
	rsize = fread(data, 1, size, fp);
	printf("read file %s ,bufsize=%d, readsize=%d\n",file, size, rsize);

	checksum = ChkSum((u_short *)data, 20);
	printf("ip head checksum = %x\n", checksum);
	fclose(fp);
	return rsize;
}

int main(int argc, char * argv[])
{
	int i;
	int tun, ret, rsize;
	unsigned char buf[4096];
	
	if(argc != 3) {
		printf("usage:%s inputfile dev\n", argv[0]);
		return 0;
	}
	
	tun = tuntap_create(argv[2]);
	if (tun < 0) {
		perror("tun_create");
		return -1;
	}
	
	if (!strstr(argv[1], "ping")) {	
		rsize = read_ip_data(argv[1], buf, sizeof(buf));
		while(rsize > 0) {
			ret = write(tun, buf, rsize);
			printf("write %d bytes\n", ret);	
			sleep(1);
		}
	} else {
		while (1) {
			unsigned char ip[4];
			
			ret = read(tun, buf, sizeof(buf));
			if (ret < 0)
				break;
			
			printf("read %d bytes", ret);
			for(i = 0 ; i < ret; i++) {
				if ( i % 16 == 0 )
					printf("\n"); 
				printf("%02x ", buf[i]);
			}
			printf("\n\n");
						
			/* swap source ip and dest ip */
			memcpy(ip, &buf[12], 4);
			memcpy(&buf[12], &buf[16], 4);
			memcpy(&buf[16], ip, 4);

			/* icmp echo reply */
			/* from 8 to 0 */
			buf[20] = 0;
			
			/* recalculate checksum */
			*((unsigned short*)&buf[22]) += 8;

			ret = write(tun, buf, ret);
			printf("write %d bytes", ret);
			for(i = 0 ; i < ret; i++) {
				if ( i % 16 == 0 )
					printf("\n"); 
				printf("%02x ", buf[i]);
			}
			printf("\n\n");
		}
	}

	return 0;
} 
