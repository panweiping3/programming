#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ext2fs/ext2_fs.h"
#include "ext2fs/ext2fs.h"
#include "e2p/e2p.h"

int main(int argc, char **argv)
{
	int fd, s_magic;
	char *devname;
	char *super_block;

	if (argc < 2)
		printf("mydumpe2fs <device>\n");
	
	devname = argv[1];
	fd = open(devname, O_RDONLY);
	if (fd <= 0)	
		printf("open %s error\n", devname);

	super_block = malloc(4096);
	if (!super_block)
		printf("memory malloc error\n");

	read(fd, super_block, 4096);

	s_magic = ((struct ext2_super_block *)super_block)->s_magic;
	if (s_magic == 0) {
		printf("Bad s_magic, Try offseting 1024\n\n");
		memset((void *)super_block, 4096, 0);
		lseek(fd, 1024, SEEK_SET);
		read(fd, super_block, 4096);
	}

	list_super((struct ext2_super_block *)super_block);

	close(fd);
	free(super_block);	
}
