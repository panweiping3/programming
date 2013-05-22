#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
#include <sys/wait.h>
#define SERV_PORT 9877
#define LISTENQ   1024
#define MAXLINE   4096
#define SA struct sockaddr

ssize_t readline(int fd, void *vptr, size_t maxlen);
void str_cli(FILE *fp,int sockfd);
int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;

	/*检测参数*/
	if(argc !=2) {
		perror("usage:tcpcli <ipaddress>");
		exit(1);
	}
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
	str_cli(stdin,sockfd);
	exit(0);
}
void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];
	while (fgets(sendline,MAXLINE,fp)!=NULL) {
		write(sockfd,sendline, strlen(sendline));
		if(readline(sockfd, recvline, MAXLINE)==0) {
			perror("str_cli:server terminated prematurely");
			exit(1);
		}
		fputs(recvline, stdout);
	}
}
/*自定义的读来自套接字的数据的函数*/
ssize_t readline(int fd, void *vptr,size_t maxlen)
{
	ssize_t     n,rc;
	char        c,*ptr;
	ptr=vptr;
	for(n=1; n< maxlen; n++)
	{
again:
		if((rc =read(fd,&c,1))==1) {
			*ptr++=c;
			if(c=='\n')
				break;
		}   else if(rc==0) {
			*ptr=0;
			return (n-1);
		} else {
			if(errno==EINTR)
				goto again;
			return (-1);
		}
	}
	*ptr=0;
	return(n);
}
