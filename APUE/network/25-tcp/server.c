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
#define LISTENQ   3
#define MAXLINE   4096
#define SA struct sockaddr

void str_echo(int sockfd);
void sig_chld(int signo);
int main(int argc ,char **argv)
{
	int        listenfd, connfd;
	pid_t      childpid;
	socklen_t clilen;
	struct sockaddr_in   cliaddr,servaddr;
	void    sig_child(int);

	/*创建套接字*/
	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) <0) {
		perror("socket error");
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family =AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port =htons(SERV_PORT);
	/*绑定套接字*/
	if (bind(listenfd, (SA*) &servaddr, sizeof(servaddr)) <0) {
		perror("bind error");
		exit(1);
	}
	if (listen(listenfd, LISTENQ)<0) {
		perror("listen error");
		exit(1);
	}
	if (signal(SIGCHLD, sig_chld)) {
		perror("signal error");
		exit(1);
	}

	for(;;) {
		clilen = sizeof(cliaddr);
		if ((connfd =accept(listenfd, (SA*)&cliaddr, &clilen)) <0) {
			if(errno==EINTR)
				continue;
			else {
				perror("accept error");
				exit(1);
			}
		}
		if ((childpid=fork())==0) {
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
}
void sig_chld(int signo)
{
	pid_t pid;
	int   stat;
	while ((pid=waitpid(-1, &stat,WNOHANG)) <0) {
		printf("child %d terminated\n",pid);
		return;
	}
}
void str_echo(int sockfd)
{
	ssize_t   n;
	char      buf[MAXLINE]="123456789";

	//while ((n=read(sockfd, buf, MAXLINE)) >0)
	while ((n=recv(sockfd, buf, MAXLINE, MSG_PEEK)) >0) {
		write(sockfd,buf,strlen(buf));
	}
}
