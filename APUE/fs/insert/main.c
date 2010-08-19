/*
 * This program is to insert some charactors into a file at offset.
 *
 * usage:
 * ./a.out filename offset data
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define KB (1024)
#define PAGE_SIZE (4 * KB)

int main(int argc, char *argv[])
{
	int fd0, fd1;
	int data_len;
	char data[PAGE_SIZE];
	struct stat stat_buf;
	unsigned long long file_size = 0;
	unsigned long long offset;

	if (argc != 4) {
		fprintf(stderr, "You should use ./a.out filename offset data\n");	
		exit(1);
	}
	
	offset = atoll(argv[2]);
	if (offset < 0) {
		fprintf(stderr, "offset error\n");	
		exit(2);
	}
	fprintf(stderr, "\n\n");	
	fprintf(stderr, "filename=%s\n", argv[1]);	
	fprintf(stderr, "offset=%lld\n", offset);	

	memset(data, '\0', PAGE_SIZE);
	strncpy(data, argv[3], PAGE_SIZE);
	data_len = strlen(data);
	fprintf(stderr, "data=%s\n", data);	
	fprintf(stderr, "data_len=%d\n", data_len);	

	fd0 = open(argv[1], O_RDWR);
	if (fd0 == -1) {
		fprintf(stderr, "open error\n");	
		exit(2);
	}
	
	if (fstat(fd0, &stat_buf)) {
		fprintf(stderr, "stat error\n");	
		exit(3);
	}
	
	file_size = stat_buf.st_size;
	fprintf(stderr, "file_size=%d\n", file_size);	
	if (offset > file_size) {
		fprintf(stderr, "offset > file_size error\n");	
		exit(2);
	}
	
	char *old_data = (char *)mmap(NULL, 
								file_size - offset, 
								PROT_READ, 
								MAP_SHARED, 
								fd0, 
								offset);
	if (old_data < 0) {
		fprintf(stderr, "mmap error\n");
		exit(4);
	}

	if (lseek(fd0, file_size + data_len, SEEK_SET) < 0) {
		fprintf(stderr, "1 seek error\n");	
		exit(6);
	}
	
	unsigned long long count = file_size - offset;
	while (count > 0) {
		write(fd0, old_data + count, 1);
		count--;
		if (lseek(fd0, offset + count, SEEK_SET) < 0) {
			fprintf(stderr, "2 seek error\n");	
			exit(6);
		}
	}
	munmap(old_data, file_size - offset);

	if (lseek(fd0, offset, SEEK_SET) < 0) {
		fprintf(stderr, "3 seek error\n");	
		exit(6);
	}
		
	write(fd0, data, data_len);
	close(fd0);
	return 0;
}
