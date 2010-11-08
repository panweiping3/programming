#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd, i;
	int data;
	fd = open("/dev/second", O_RDONLY);
	if (fd < 0) {
		printf("open /dev/second error\n");
	} else {
		for(i = 0; i < 20; i++) {
			read(fd, &data, sizeof(data));
			printf("read /dev/second is %d\n",data);
			sleep(1);
		}
	}
	close(fd);

	return 0;
}
