#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int fd = -1;
	FILE *fp = NULL;
	char *buf  = "hello world\n";
	char buf1[20];
	int buf_size = strlen(buf);
	
	errno = 0;
	if ((fd = open("./tmpfile", O_RDWR | O_CREAT | O_EXCL)) < 0)
	{
		if (errno == EEXIST)
		{
			if ((fd = open("./tmpfile", O_WRONLY | O_TRUNC)) < 0)
			{
				perror("can't truncate tmpfile");
				exit(1);
			}
			
		}
		else
		{
			perror("open tmpfile error");
			exit(1);
		}
	}

	printf("tmpfile fd is:%d\n", fd);
	
#if 0	
	if (write(fd, buf, buf_size) != buf_size)
	{
		perror("write error");
		exit(3);
	}
#endif	
	
	if ((fp = fdopen(fd, "a")) == NULL)
	{
		perror("fdopen error");
		exit(3);
	}

	if (fwrite(buf, sizeof(char), buf_size, fp) != buf_size)
	{
		perror("fiwrite error");
		exit(3);
	}
#if 0
	if (fflush(fp) == EOF)
	{
		perror("fflush error");
		exit(3);
	}
	if (fseek(fp, 0, SEEK_SET) < 0)
	{
		perror("lseek error");
		exit(3);
	}
#endif
		
	if (read(fd, buf1, buf_size) != buf_size)
	{
		perror("read error");
		exit(3);
	}

	fprintf(stdout, "%s\n", buf1);
#if 0
	if (unlink("./tmpfile") < 0)
	{
		perror("unlink tmpfile error");
		exit(2);
	}
#endif
}
